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
    RandomEngine(uint32_t seed = 3141592653UL) : x(seed) {};

    uint32_t operator()() {
        x ^= x << 13; x ^= x >> 17; x ^= x << 15;
        return x;
    }

    uint32_t operator()(uint32_t max) {
        return (*this)() % max;
    };

    uint32_t operator()(uint32_t min, uint32_t max) {
        assert(min < max);
        return min + (*this)(max - min);
    };

  private:
    uint32_t x;
};

signed main() {
    int n; cin >> n;
    RandomEngine engine;
    for(int i=0; i<n; ++i) cout << engine() << "\n";
    for(int i=0; i<n; ++i) cout << engine(5) << "\n";
    for(int i=0; i<n; ++i) cout << engine(5, 10) << "\n";
}
