// vmath performance suite.
//
// Measures execution time of challenging sequences of vmath operations
// (dependent multiply chains, matrix inversions, quaternion slerp, type
// conversions, and a realistic scene-graph pipeline) for both float and double.
//
// IMPORTANT: always build/run in optimized mode, otherwise the numbers are
// meaningless (bazel defaults to -O0 "fastbuild"):
//
//     bazel run -c opt //benchmark:vmath_benchmark
//     bazel run -c opt //benchmark:vmath_benchmark -- --save benchmark/baseline.txt
//     bazel run -c opt //benchmark:vmath_benchmark -- --baseline benchmark/baseline.txt --check
//
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

#include "benchmark_util.h"
#include "vmath.h"

namespace {

// Workload sizes. BATCH is used for independent (data-parallel) operations;
// CHAIN is used for dependent sequences where each step consumes the previous
// result (the "challenging" latency-bound case).
constexpr size_t BATCH = 4096;
constexpr size_t CHAIN = 1024;

// ------------------------------------------------------------------ //
// Deterministic random data generators (fixed seed => reproducible).  //
// ------------------------------------------------------------------ //

struct Rng {
    std::mt19937 gen{0xC0FFEEu};
    std::uniform_real_distribution<double> dist{-1.0, 1.0};
    template <typename T> T next() { return static_cast<T>(dist(gen)); }
};

template <typename T> math::Vector3<T> rand_vec3(Rng &r) {
    // avoid the exact zero vector so normalize() is well defined
    return math::Vector3<T>(r.next<T>() + T(1.5), r.next<T>() + T(1.5), r.next<T>() + T(1.5));
}

template <typename T> math::Vector4<T> rand_vec4(Rng &r) {
    return math::Vector4<T>(r.next<T>() + T(1.5), r.next<T>() + T(1.5), r.next<T>() + T(1.5), r.next<T>() + T(1.5));
}

template <typename T> math::Quaternion<T> rand_quat(Rng &r) {
    // random rotation quaternion (normalized)
    return math::normalized(math::quat_from_euler_321<T>(r.next<T>() * T(3.1), r.next<T>() * T(3.1), r.next<T>() * T(3.1)));
}

template <typename T> math::Matrix4<T> rand_transform_mat4(Rng &r) {
    // rigid transform => always invertible
    return math::create_transformation<T>(rand_vec3<T>(r), rand_quat<T>(r));
}

template <typename T> math::Matrix3<T> rand_rot_mat3(Rng &r) {
    return math::rot_matrix<T>(rand_quat<T>(r));
}

template <typename T> math::Transform<T> rand_transform(Rng &r) {
    return math::Transform<T>(rand_vec3<T>(r), rand_quat<T>(r));
}

template <typename Gen> auto make_vec(size_t n, Gen g) -> std::vector<decltype(g())> {
    std::vector<decltype(g())> v;
    v.reserve(n);
    for (size_t i = 0; i < n; ++i)
        v.push_back(g());
    return v;
}

// ------------------------------------------------------------------ //
// Benchmark registration (templated over the scalar type).           //
// ------------------------------------------------------------------ //

template <typename T> void register_benchmarks(bench::Suite &suite, const std::string &sfx) {
    Rng r;

    // ---- Vector3 ----
    {
        auto v = make_vec(BATCH, [&] { return rand_vec3<T>(r); });
        suite.add("vec3_normalize/" + sfx, BATCH, [v] {
            double s = 0;
            for (const auto &e : v) {
                auto n = math::normalized(e);
                s += n.x + n.y + n.z;
            }
            return s;
        });
        suite.add("vec3_dot/" + sfx, BATCH - 1, [v] {
            double s = 0;
            for (size_t i = 1; i < v.size(); ++i)
                s += v[i].dot(v[i - 1]);
            return s;
        });
        suite.add("vec3_cross/" + sfx, BATCH - 1, [v] {
            double s = 0;
            for (size_t i = 1; i < v.size(); ++i) {
                auto c = v[i].cross(v[i - 1]);
                s += c.x + c.y + c.z;
            }
            return s;
        });
    }

    // ---- Vector4 ----
    {
        auto v = make_vec(BATCH, [&] { return rand_vec4<T>(r); });
        suite.add("vec4_normalize/" + sfx, BATCH, [v] {
            double s = 0;
            for (const auto &e : v) {
                auto n = math::normalized(e);
                s += n.x + n.y + n.z + n.w;
            }
            return s;
        });
    }

    // ---- Matrix3 ----
    {
        auto m = make_vec(BATCH, [&] { return rand_rot_mat3<T>(r); });
        suite.add("mat3_mul_batch/" + sfx, BATCH - 1, [m] {
            double s = 0;
            for (size_t i = 1; i < m.size(); ++i) {
                auto p = m[i] * m[i - 1];
                s += p.data[0];
            }
            return s;
        });
        suite.add("mat3_inverse/" + sfx, BATCH, [m] {
            double s = 0;
            for (const auto &e : m) {
                auto inv = math::inverse(e);
                s += inv.data[0];
            }
            return s;
        });
    }

    // ---- Matrix4 ----
    {
        auto m = make_vec(BATCH, [&] { return rand_transform_mat4<T>(r); });
        auto chain = make_vec(CHAIN, [&] { return rand_transform_mat4<T>(r); });
        auto v4 = make_vec(BATCH, [&] { return rand_vec4<T>(r); });
        auto v3 = make_vec(BATCH, [&] { return rand_vec3<T>(r); });

        suite.add("mat4_mul_batch/" + sfx, BATCH - 1, [m] {
            double s = 0;
            for (size_t i = 1; i < m.size(); ++i) {
                auto p = m[i] * m[i - 1];
                s += p.data[0];
            }
            return s;
        });
        suite.add("mat4_mul_chain/" + sfx, CHAIN - 1, [chain] {
            auto acc = chain[0];
            for (size_t i = 1; i < chain.size(); ++i)
                acc = acc * chain[i]; // dependent: latency-bound
            return double(acc.data[0] + acc.data[5]);
        });
        suite.add("mat4_inverse/" + sfx, BATCH, [m] {
            double s = 0;
            for (const auto &e : m) {
                auto inv = math::inverse(e);
                s += inv.data[0];
            }
            return s;
        });
        suite.add("mat4_transpose/" + sfx, BATCH, [m] {
            double s = 0;
            for (auto e : m) {
                math::transpose(e);
                s += e.data[1];
            }
            return s;
        });
        suite.add("mat4_mul_vec4/" + sfx, BATCH, [m, v4] {
            double s = 0;
            for (size_t i = 0; i < m.size(); ++i) {
                auto out = m[i] * v4[i];
                s += out.x + out.y + out.z + out.w;
            }
            return s;
        });
        suite.add("mat4_mul_vec3/" + sfx, BATCH, [m, v3] {
            double s = 0;
            for (size_t i = 0; i < m.size(); ++i) {
                auto out = m[i] * v3[i];
                s += out.x + out.y + out.z;
            }
            return s;
        });
    }

    // ---- Quaternion ----
    {
        auto q = make_vec(BATCH, [&] { return rand_quat<T>(r); });
        auto chain = make_vec(CHAIN, [&] { return rand_quat<T>(r); });
        auto v3 = make_vec(BATCH, [&] { return rand_vec3<T>(r); });

        suite.add("quat_mul_batch/" + sfx, BATCH - 1, [q] {
            double s = 0;
            for (size_t i = 1; i < q.size(); ++i) {
                auto p = q[i] * q[i - 1];
                s += p.w;
            }
            return s;
        });
        suite.add("quat_mul_chain/" + sfx, CHAIN - 1, [chain] {
            auto acc = chain[0];
            for (size_t i = 1; i < chain.size(); ++i)
                acc = acc * chain[i]; // dependent
            return double(acc.w + acc.x);
        });
        suite.add("quat_normalize/" + sfx, BATCH, [q] {
            double s = 0;
            for (const auto &e : q) {
                auto n = math::normalized(e);
                s += n.w;
            }
            return s;
        });
        suite.add("quat_rotate_vec3/" + sfx, BATCH, [q, v3] {
            double s = 0;
            for (size_t i = 0; i < q.size(); ++i) {
                auto out = q[i].rotate(v3[i]);
                s += out.x + out.y + out.z;
            }
            return s;
        });
        suite.add("quat_slerp/" + sfx, BATCH - 1, [q] {
            double s = 0;
            for (size_t i = 1; i < q.size(); ++i) {
                auto out = math::slerp(q[i - 1], q[i], T(0.37));
                s += out.w;
            }
            return s;
        });
    }

    // ---- Conversions / factories ----
    {
        auto q = make_vec(BATCH, [&] { return rand_quat<T>(r); });
        auto m = make_vec(BATCH, [&] { return rand_transform_mat4<T>(r); });
        auto eyes = make_vec(BATCH, [&] { return rand_vec3<T>(r); });
        auto tgts = make_vec(BATCH, [&] { return rand_vec3<T>(r); });

        suite.add("quat_to_mat3/" + sfx, BATCH, [q] {
            double s = 0;
            for (const auto &e : q) {
                auto rm = math::rot_matrix(e);
                s += rm.data[0];
            }
            return s;
        });
        suite.add("mat4_to_quat/" + sfx, BATCH, [m] {
            double s = 0;
            for (const auto &e : m) {
                auto qq = math::quat_from_matrix(e);
                s += qq.w;
            }
            return s;
        });
        suite.add("quat_to_euler_321/" + sfx, BATCH, [q] {
            double s = 0;
            for (const auto &e : q) {
                auto ea = math::to_euler_321(e);
                s += ea.x + ea.y + ea.z;
            }
            return s;
        });
        suite.add("create_lookat/" + sfx, BATCH, [eyes, tgts] {
            double s = 0;
            for (size_t i = 0; i < eyes.size(); ++i) {
                auto la = math::create_lookat<T>(eyes[i], tgts[i]);
                s += la.data[0];
            }
            return s;
        });
    }

    // ---- Transform (rigid) ----
    {
        auto t = make_vec(BATCH, [&] { return rand_transform<T>(r); });
        auto chain = make_vec(CHAIN, [&] { return rand_transform<T>(r); });
        auto v3 = make_vec(BATCH, [&] { return rand_vec3<T>(r); });

        suite.add("transform_compose_chain/" + sfx, CHAIN - 1, [chain] {
            auto acc = chain[0];
            for (size_t i = 1; i < chain.size(); ++i)
                acc = acc * chain[i]; // dependent
            return double(acc.p.x + acc.q.w);
        });
        suite.add("transform_point/" + sfx, BATCH, [t, v3] {
            double s = 0;
            for (size_t i = 0; i < t.size(); ++i) {
                auto out = t[i].transform(v3[i]);
                s += out.x + out.y + out.z;
            }
            return s;
        });
        suite.add("transform_inverse/" + sfx, BATCH, [t] {
            double s = 0;
            for (const auto &e : t) {
                auto inv = e.inverse();
                s += inv.p.x + inv.q.w;
            }
            return s;
        });
    }

    // ---- Realistic pipeline: a small "scene graph" frame ----
    // For each node: compose a local transform onto a running parent transform,
    // convert the world transform to a Matrix4, and transform a point with it.
    // This mixes quaternion algebra, transform composition and matrix build/apply
    // the way a typical animation/rendering update would.
    {
        auto locals = make_vec(CHAIN, [&] { return rand_transform<T>(r); });
        auto points = make_vec(CHAIN, [&] { return rand_vec3<T>(r); });
        suite.add("scene_graph_update/" + sfx, CHAIN, [locals, points] {
            math::Transform<T> world;
            double s = 0;
            for (size_t i = 0; i < locals.size(); ++i) {
                world = world * locals[i];
                auto mat = math::create_transformation<T>(world.p, world.q);
                auto p = mat * points[i];
                s += p.x + p.y + p.z;
            }
            return s;
        });
    }
}

// ------------------------------------------------------------------ //
// Reporting & comparison                                             //
// ------------------------------------------------------------------ //

void print_results(const std::vector<bench::Result> &results) {
    printf("\n%-32s %10s %14s %14s\n", "benchmark", "ops", "ns/op(best)", "ns/op(median)");
    printf("%-32s %10s %14s %14s\n", "--------------------------------", "----------", "--------------",
           "--------------");
    for (const auto &r : results)
        printf("%-32s %10llu %14.3f %14.3f\n", r.name.c_str(), (unsigned long long)r.ops, r.ns_per_op_best,
               r.ns_per_op_median);
    printf("\n");
}

// Returns number of regressions worse than `threshold` percent.
int compare_to_baseline(const std::vector<bench::Result> &results, const std::map<std::string, double> &base,
                        double threshold) {
    printf("comparison vs baseline (threshold %.1f%%):\n", threshold);
    printf("%-32s %14s %14s %10s\n", "benchmark", "baseline", "current", "delta");
    printf("%-32s %14s %14s %10s\n", "--------------------------------", "--------------", "--------------",
           "----------");
    int regressions = 0;
    int missing = 0;
    for (const auto &r : results) {
        auto it = base.find(r.name);
        if (it == base.end()) {
            printf("%-32s %14s %14.3f %10s\n", r.name.c_str(), "-", r.ns_per_op_best, "(new)");
            ++missing;
            continue;
        }
        double old = it->second;
        double cur = r.ns_per_op_best;
        double delta = old > 0 ? (cur - old) / old * 100.0 : 0.0;
        const char *tag = "";
        if (delta > threshold) {
            tag = "  SLOWER";
            ++regressions;
        } else if (delta < -threshold) {
            tag = "  faster";
        }
        printf("%-32s %14.3f %14.3f %+9.1f%%%s\n", r.name.c_str(), old, cur, delta, tag);
    }
    printf("\n%d regression(s) above %.1f%%, %d new benchmark(s) not in baseline.\n", regressions, threshold, missing);
    return regressions;
}

void print_usage(const char *prog) {
    printf("usage: %s [options]\n", prog);
    printf("  --reps N            repetitions per benchmark (default 50)\n");
    printf("  --filter SUBSTR     only run benchmarks whose name contains SUBSTR\n");
    printf("  --save PATH         write current results as a baseline file\n");
    printf("  --baseline PATH     compare current results against a baseline file\n");
    printf("  --threshold PCT     regression threshold percent for --check (default 10)\n");
    printf("  --check             exit non-zero if any regression exceeds threshold\n");
    printf("  -h, --help          show this help\n");
    printf("\nBuild/run optimized:  bazel run -c opt //benchmark:vmath_benchmark\n");
}

} // namespace

int main(int argc, char **argv) {
    int reps = 50;
    double threshold = 10.0;
    bool check = false;
    std::string save_path, baseline_path, filter;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto need_val = [&](const char *name) -> std::string {
            if (i + 1 >= argc) {
                fprintf(stderr, "error: missing value for %s\n", name);
                exit(2);
            }
            return argv[++i];
        };
        if (a == "--reps")
            reps = std::atoi(need_val("--reps").c_str());
        else if (a == "--threshold")
            threshold = std::atof(need_val("--threshold").c_str());
        else if (a == "--filter")
            filter = need_val("--filter");
        else if (a == "--save")
            save_path = need_val("--save");
        else if (a == "--baseline")
            baseline_path = need_val("--baseline");
        else if (a == "--check")
            check = true;
        else if (a == "-h" || a == "--help") {
            print_usage(argv[0]);
            return 0;
        } else {
            fprintf(stderr, "error: unknown argument '%s'\n", a.c_str());
            print_usage(argv[0]);
            return 2;
        }
    }
    if (reps < 1)
        reps = 1;

    bench::Suite suite;
    register_benchmarks<float>(suite, "f");
    register_benchmarks<double>(suite, "d");

    printf("running vmath benchmarks (reps=%d)...\n", reps);
    auto results = suite.run(reps, filter);
    print_results(results);

    if (!save_path.empty()) {
        bench::save_baseline(save_path, results);
        printf("saved baseline to %s\n", save_path.c_str());
    }

    int rc = 0;
    if (!baseline_path.empty()) {
        auto base = bench::load_baseline(baseline_path);
        if (base.empty())
            fprintf(stderr, "warning: baseline '%s' is empty or missing\n", baseline_path.c_str());
        int regressions = compare_to_baseline(results, base, threshold);
        if (check && regressions > 0)
            rc = 1;
    }
    return rc;
}
