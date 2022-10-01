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

using namespace std;

#define INF32 2147483647

using Integer = int32_t;
using UnsignedInteger = uint32_t;

using Time = int32_t;
using Score = int32_t;
using Hash = uint32_t;

constexpr Hash HASH_MAX = numeric_limits<Hash>::max();

unordered_map<Hash,int> mp;

signed main() {
    for(int i=0; i<61*61*61*61; ++i) {
        Hash v = i * 2654435761UL % HASH_MAX;
        // debug(v);
        if(mp[v]) {
            debug("confrict!!", v);
        }
        ++mp[v];
    }
}
