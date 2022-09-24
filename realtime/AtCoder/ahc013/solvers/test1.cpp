/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#ifdef LOCAL_JUDGE
    #include<debug>
    #define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
    #define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
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

#include <iostream>
#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;

struct RandomEngine {
    RandomEngine(uint64_t seed = 3141592653589793238UL) {
        // engine.seed(seed);
        w ^= seed;
        w ^= (uint64_t)w >> 21; w ^= (uint64_t)w << 35; w ^= (uint64_t)w >> 4;
        w *= 2685821657736338717LL;
        debug(w);
    }

    uint32_t generate() {
        debug(x, y, z, w);
        uint32_t t;
        t = (x ^ (x << 11)); x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        // return engine();
    }

    uint32_t range(uint32_t max) {
        return this->generate() % max;
    }

    uint32_t range(uint32_t min, uint32_t max) {
        dev_assert(min < max);
        return min + this->range(max - min);
    }

  private:
    uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    // mt19937 engine;
};

signed main() {
    int n; cin >> n;
    // for(int i=0; i<n; ++i) cout << xor128() << "\n";
    RandomEngine engine;
    for(int i=0; i<n; ++i) cout << engine.generate() << "\n";
    for(int i=0; i<n; ++i) cout << engine.range(5) << "\n";
    for(int i=0; i<n; ++i) cout << engine.range(5, 10) << "\n";
}
