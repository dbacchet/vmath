# vmath performance suite

`vmath_benchmark` measures the execution time of challenging sequences of vmath
operations and can record / compare against a performance **baseline**, so that
future changes can be checked for regressions.

## What it measures

Each benchmark is run for both `float` (`/f`) and `double` (`/d`) and reports
**nanoseconds per primitive operation** (best and median over several
repetitions). The suite covers:

- **Vectors** — normalize, dot, cross (`vec3_*`, `vec4_*`)
- **Matrices** — multiply (batch + dependent chain), inverse, transpose,
  matrix×vector (`mat3_*`, `mat4_*`)
- **Quaternions** — multiply (batch + chain), normalize, rotate-vector, slerp
  (`quat_*`)
- **Conversions / factories** — quat↔matrix, quat→euler, look-at
- **Transforms** — rigid compose chain, transform point, inverse (`transform_*`)
- **A realistic pipeline** — `scene_graph_update`, which walks a chain of nodes
  composing transforms, building a `Matrix4` per node and transforming a point
  (mimics a per-frame animation/render update).

"Chain" benchmarks feed each result into the next step (latency-bound, the
hardest case for the CPU); "batch" benchmarks process independent items
(throughput-bound).

The harness (`benchmark_util.h`) uses a per-benchmark warmup pass, takes the
**minimum** time as the headline metric (most stable under system noise), and
routes every result through `do_not_optimize()` so the compiler cannot eliminate
the work. At startup the tool also spins for ~200 ms so the CPU reaches a steady
(boosted) frequency before any measurement — without this the first (cheapest)
benchmarks are biased by the frequency ramp-up.

With the defaults (`--reps 100` + warmup), run-to-run variability on the
reference machine is small: all 50 benchmarks stay within ~7% across repeated
runs (most within 3%), so the default 10% regression threshold is comfortable.

## Running

Always build in **optimized** mode — bazel defaults to `-O0` (`fastbuild`),
which makes the numbers meaningless:

```sh
# run all benchmarks and print the table
bazel run -c opt //benchmark:vmath_benchmark

# run a subset
bazel run -c opt //benchmark:vmath_benchmark -- --filter mat4

# more repetitions (better min estimate on a noisy machine)
bazel run -c opt //benchmark:vmath_benchmark -- --reps 400
```

### Record a baseline

```sh
bazel run -c opt //benchmark:vmath_benchmark -- --save $(pwd)/benchmark/baseline.txt
```

### Compare against the baseline (after making changes)

```sh
# print per-benchmark deltas vs the baseline
bazel run -c opt //benchmark:vmath_benchmark -- --baseline $(pwd)/benchmark/baseline.txt

# fail (exit code 1) if any benchmark regresses by more than the threshold %
bazel run -c opt //benchmark:vmath_benchmark -- \
    --baseline $(pwd)/benchmark/baseline.txt --check --threshold 10
```

Deltas are `(current - baseline) / baseline`; positive means slower. Results
slower than `--threshold` (default 10%) are marked `SLOWER` and counted as
regressions for `--check`.

## Options

| flag | meaning |
|------|---------|
| `--reps N` | repetitions per benchmark (default 100) |
| `--filter SUBSTR` | only run benchmarks whose name contains `SUBSTR` |
| `--save PATH` | write current results as a baseline file |
| `--baseline PATH` | compare current results against a baseline file |
| `--threshold PCT` | regression threshold percent for `--check` (default 10) |
| `--check` | exit non-zero if any regression exceeds the threshold |

## Baseline

> **Note:** absolute numbers are machine-, compiler- and load-dependent. The
> committed `baseline.txt` is a reference point; regenerate it on your own
> machine before relying on `--check`. Always compare runs done on the *same*
> machine in a quiet state.

Reference baseline recorded with:

- **CPU:** Apple M2
- **OS:** macOS 26.5.1
- **Compiler:** Apple clang 21.0.0, `-c opt` (`-O2`), C++14
- **bazel:** 8.4.2, `--reps 100`

Headline metric is `ns/op(best)`. Selected highlights (see `baseline.txt` for
the full set):

| benchmark | float ns/op | double ns/op |
|-----------|------------:|-------------:|
| vec3_normalize | 0.95 | 1.06 |
| mat3_inverse | 1.80 | 1.73 |
| mat4_mul_batch | 0.93 | 1.23 |
| mat4_mul_chain | 4.81 | 4.68 |
| mat4_inverse | 29.66 | 26.59 |
| mat4_mul_vec4 | 1.84 | 1.70 |
| quat_mul_chain | 4.60 | 4.81 |
| quat_rotate_vec3 | 0.86 | 1.51 |
| quat_slerp | 14.68 | 21.79 |
| mat4_to_quat | 5.40 | 2.38 |
| quat_to_euler_321 | 19.44 | 45.25 |
| transform_compose_chain | 4.85 | 5.01 |
| scene_graph_update | 7.32 | 7.45 |

The clear hotspots are `mat4_inverse`, `quat_to_euler_321` and `quat_slerp` —
good candidates if optimization work is ever needed.
