// Minimal, dependency-free micro-benchmark harness used by the vmath
// performance suite. It provides:
//   - do_not_optimize(): prevents the compiler from eliminating benchmarked work
//   - Suite: register named benchmarks and run them with warmup + repetitions
//   - baseline save / load / compare: persist a performance baseline and detect
//     regressions on later runs
//
// Each benchmark returns a `double` checksum derived from its results; the
// harness feeds it into a volatile sink so the optimizer cannot discard the
// computation. Timings are reported as nanoseconds per primitive operation
// (the "ops" count declared at registration time), using the *best* (minimum)
// observed time as the headline metric because it is the most stable under
// system noise, plus the median for reference.
#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace bench {

/// Prevent the compiler from optimizing away `value` (and any computation that
/// produced it). Works on gcc/clang.
template <typename T> inline void do_not_optimize(const T &value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

using clock_type = std::chrono::steady_clock;

struct Result {
    std::string name;
    uint64_t ops = 0;         ///< primitive operations performed per run
    double ns_per_op_best = 0; ///< min over repetitions (headline metric)
    double ns_per_op_median = 0;
};

struct Benchmark {
    std::string name;
    uint64_t ops;
    std::function<double()> fn;
};

class Suite {
  public:
    /// Register a benchmark. `ops` is the number of primitive operations the
    /// function performs in a single call (used to normalize timings).
    void add(const std::string &name, uint64_t ops, std::function<double()> fn) {
        benches_.push_back({name, ops, std::move(fn)});
    }

    std::vector<Result> run(int reps, const std::string &filter) {
        std::vector<Result> results;
        for (auto &b : benches_) {
            if (!filter.empty() && b.name.find(filter) == std::string::npos)
                continue;
            results.push_back(run_one(b, reps));
        }
        return results;
    }

  private:
    Result run_one(const Benchmark &b, int reps) {
        volatile double sink = 0.0;
        sink += b.fn(); // warmup (also warms caches / branch predictors)

        std::vector<double> per_op;
        per_op.reserve(static_cast<size_t>(reps));
        for (int r = 0; r < reps; ++r) {
            auto t0 = clock_type::now();
            double checksum = b.fn();
            auto t1 = clock_type::now();
            sink += checksum;
            double ns = std::chrono::duration<double, std::nano>(t1 - t0).count();
            per_op.push_back(ns / static_cast<double>(b.ops));
        }
        do_not_optimize(sink);

        std::sort(per_op.begin(), per_op.end());
        Result res;
        res.name = b.name;
        res.ops = b.ops;
        res.ns_per_op_best = per_op.front();
        res.ns_per_op_median = per_op[per_op.size() / 2];
        return res;
    }

    std::vector<Benchmark> benches_;
};

inline void save_baseline(const std::string &path, const std::vector<Result> &results) {
    std::ofstream out(path);
    out << "# vmath benchmark baseline\n";
    out << "# columns: name<TAB>ns_per_op(best)\n";
    for (const auto &r : results)
        out << r.name << '\t' << r.ns_per_op_best << '\n';
}

inline std::map<std::string, double> load_baseline(const std::string &path) {
    std::map<std::string, double> m;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream ss(line);
        std::string name;
        double v = 0;
        if (std::getline(ss, name, '\t') && (ss >> v) && !name.empty())
            m[name] = v;
    }
    return m;
}

} // namespace bench
