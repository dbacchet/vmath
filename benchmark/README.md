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

The harness (`benchmark_util.h`) uses a warmup pass, takes the **minimum** time
as the headline metric (most stable under system noise), and routes every result
through `do_not_optimize()` so the compiler cannot eliminate the work.

## Running

Always build in **optimized** mode — bazel defaults to `-O0` (`fastbuild`),
which makes the numbers meaningless:

```sh
# run all benchmarks and print the table
bazel run -c opt //benchmark:vmath_benchmark

# run a subset
bazel run -c opt //benchmark:vmath_benchmark -- --filter mat4

# more repetitions (better min estimate on a noisy machine)
bazel run -c opt //benchmark:vmath_benchmark -- --reps 200
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
| `--reps N` | repetitions per benchmark (default 50) |
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
- **bazel:** 8.4.2, `--reps 50`

Headline metric is `ns/op(best)`. Selected highlights (see `baseline.txt` for
the full set):

| benchmark | float ns/op | double ns/op |
|-----------|------------:|-------------:|
| vec3_normalize | 1.52 | 1.21 |
| mat3_inverse | 2.47 | 1.97 |
| mat4_mul_batch | 1.24 | 1.41 |
| mat4_mul_chain | 6.23 | 5.34 |
| mat4_inverse | 38.45 | 28.49 |
| mat4_mul_vec4 | 2.52 | 1.93 |
| quat_mul_chain | 5.99 | 5.25 |
| quat_rotate_vec3 | 1.11 | 1.67 |
| quat_slerp | 17.81 | 23.10 |
| mat4_to_quat | 3.10 | 2.66 |
| quat_to_euler_321 | 26.94 | 47.73 |
| transform_compose_chain | 5.82 | 4.97 |
| scene_graph_update | 8.67 | 7.45 |

The clear hotspots are `mat4_inverse`, `quat_to_euler_321` and `quat_slerp` —
good candidates if optimization work is ever needed.
