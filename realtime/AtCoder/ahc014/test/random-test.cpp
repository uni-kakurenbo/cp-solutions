/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
 /* #language C++ GCC */

 // #pragma GCC target("avx")
 // #pragma GCC optimize("Ofast")
 // #pragma GCC optimize("unroll-loops")

#ifdef LOCAL_JUDGE
#include<debug>
#define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { Debug::DEBUG(nintptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nintptr, "\033[m\n"); } while(0);
#else
#define debug(...) { ; }
#define DEBUG(...) { ; }
#endif

#include <cassert>

#ifdef LOCAL_JUDGE
#define dev_assert(...) assert(__VA_ARGS__)
#else
#define dev_assert(...) { ; }
#endif

#include <cstdint>
#include <chrono>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <set>
#include <bitset>
#include <array>
#include <vector>
#include <deque>
#include <utility>
#include <tuple>
#include <algorithm>
#include <random>
#include <numeric>
#include <memory>
#include <optional>
#include <map>

using namespace std;

#define INF32 2147483647

using Integer = int32_t;
using UnsignedInteger = uint32_t;

using Time = int32_t;
using Score = int32_t;
using Hash = uint32_t;

constexpr Hash HASH_MAX = numeric_limits<Hash>::max();

constexpr Integer MAX_N = 61;
constexpr Integer MIN_N = 31;

constexpr Integer DX[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
constexpr Integer DY[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };

class Timer {
  private:
    const Time time_limit;
    chrono::system_clock::time_point clock_start;

  public:
    Timer(const Time time_limit = 0) : time_limit(time_limit), clock_start(chrono::system_clock::now()) {}

    inline Timer* reset() {
        clock_start = chrono::system_clock::now();
        return this;
    }

    inline Time elapsed() const {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - this->clock_start).count();
    }

    inline bool expired() const { return this->elapsed() > time_limit; }
};

template<class Engine = mt19937> struct RandomEngine {
    static constexpr UnsignedInteger MIN = Engine::min();
    static constexpr UnsignedInteger MAX = Engine::max();

    static constexpr UnsignedInteger min() { return MIN; }
    static constexpr UnsignedInteger max() { return MAX; }

    RandomEngine(UnsignedInteger seed = 3141592653UL) {
        engine.seed(seed);
    };

    inline UnsignedInteger operator()() {
        return engine();
    }

    inline UnsignedInteger operator()(UnsignedInteger max) {
        return (*this)() % max;
    }
    inline Integer operator()(Integer min, Integer max) {
        dev_assert(min <= max);
        if(min == max) return min;
        return min + (*this)(max - min);
    };

  private:
    Engine engine;
};

template<Integer MEAN, Integer VARIANCE, class Engine = mt19937> struct NoiseGenerator {
    normal_distribution<float_t> distr;

    NoiseGenerator() : distr(MEAN, VARIANCE) {}

    inline Integer operator()() {
        return distr(engine);
    }

  private:
    Engine engine;
};

NoiseGenerator<0, 10> noise_generator;

signed main() {
    map<int,int> cnt;
    for(int i=0; i<10000; ++i) {
        int v = noise_generator();
        // cout << v << "\n";
        ++cnt[v];
    }
    for(auto [k, v] : cnt) {
        cout << k << ": " << v << "\n";
    }

}
