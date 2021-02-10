#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <random>
#include <vector>
#include <chrono>

#include "vmath.h"

template <typename T> T rand_range(T v1, T v2) {
    return v1 + T(double(rand()) / RAND_MAX * (v2 - v1));
}

template <typename T> math::Matrix4<T> create_random_mat4() {
    return math::create_transformation(
        math::Vector3<T>(rand_range(T(0), T(1)), rand_range(T(0), T(1)), rand_range(T(0), T(1))),
        math::quat_from_euler_321(rand_range(T(0), T(1)), rand_range(T(0), T(1)), rand_range(T(0), T(1))));
}

template <typename T> math::Transform<T> create_random_transf() {
    return math::Transform<T>(
        math::Vector3<T>(rand_range(T(0), T(1)), rand_range(T(0), T(1)), rand_range(T(0), T(1))),
        math::quat_from_euler_321(rand_range(T(0), T(1)), rand_range(T(0), T(1)), rand_range(T(0), T(1))));
}

template <typename T> void profile_mat4(std::vector<math::Matrix4<T>> &chain) {
    for (uint32_t i = 1; i < chain.size(); i++) {
        // printf("mat4 %d %d\n", i, rand());
        chain[i] = chain[i] * chain[i - 1];
    }
}

template <typename T> void profile_transform(std::vector<math::Transform<T>> &chain) {
    for (uint32_t i = 1; i < chain.size(); i++) {
        // printf("transform %d %d\n", i, rand());
        chain[i] = chain[i] * chain[i - 1];
    }
}

int main(int argc, char *argv[]) {
    int32_t len = argc > 1 ? std::atoi(argv[1]) : 100;
    uint32_t seed = argc > 2 ? std::atoi(argv[2]) : 12345678;
    {
        printf("\n[FLOAT] start benchmark\n");
        // profile mat4 (float)
        std::vector<math::Matrix4f> chain_mat4_f;
        std::vector<math::Transff> chain_transf_f;
        srand(seed);
        for (int i = 0; i < len; i++) {
            chain_mat4_f.push_back(create_random_mat4<float>());
        }
        auto start = std::chrono::high_resolution_clock::now();
        profile_mat4(chain_mat4_f);
        auto dur =
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        printf("mat4 elapsed time:   %ld ns\n", dur.count());

        // profile transf (float)
        srand(seed);
        for (int i = 0; i < len; i++) {
            chain_transf_f.push_back(create_random_transf<float>());
        }
        start = std::chrono::high_resolution_clock::now();
        profile_transform(chain_transf_f);
        dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        printf("transf elapsed time: %ld ns\n", dur.count());

        printf("[FLOAT] benchmark complete:\n");
        const auto &tm = math::translation(chain_mat4_f.back());
        printf("final mat translation: %f %f %f\n", tm[0], tm[1], tm[2]);
        const auto &tt = chain_transf_f.back().p;
        printf("final transf translation: %f %f %f\n", tt[0], tt[1], tt[2]);
    }
    {
        printf("\n[DOUBLE] start benchmark\n");
        // profile mat4 (double)
        std::vector<math::Matrix4d> chain_mat4_d;
        std::vector<math::Transfd> chain_transf_d;
        srand(seed);
        for (int i = 0; i < len; i++) {
            chain_mat4_d.push_back(create_random_mat4<double>());
        }
        auto start = std::chrono::high_resolution_clock::now();
        profile_mat4(chain_mat4_d);
        auto dur =
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        printf("mat4 elapsed time:   %ld ns\n", dur.count());

        // profile transf (double)
        srand(seed);
        for (int i = 0; i < len; i++) {
            chain_transf_d.push_back(create_random_transf<double>());
        }
        start = std::chrono::high_resolution_clock::now();
        profile_transform(chain_transf_d);
        dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        printf("transf elapsed time: %ld ns\n", dur.count());

        printf("[DOUBLE] benchmark complete:\n");
        const auto &tm = math::translation(chain_mat4_d.back());
        printf("final mat translation: %f %f %f\n", tm[0], tm[1], tm[2]);
        const auto &tt = chain_transf_d.back().p;
        printf("final transf translation: %f %f %f\n", tt[0], tt[1], tt[2]);
    }
    return 0;
}

