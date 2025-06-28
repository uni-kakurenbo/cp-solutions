/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>
using namespace std;
namespace rng = std::ranges;

void solve();

signed main() {
    // debug(__cplusplus);
    // int $ = 1;
    // std::cin >> $;
    for(;;) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using i32 = int;
using i64 = long;

// #include "template/warnings.hpp"
void solve() {
    i32 n; std::cin >> n;
    if(n == 0) exit(0);

    vector<i32> a(n);
    for(auto& x: a) std::cin >> x;

    auto s = 0, t = 0;
    for(auto x : a) s += x, t += x;
    s /= 3;
    s += 50;

    vector dp(s, vector<i32>(s));
    dp[0][0] = true;

    for(auto x : a) {
        for(i32  i : std::views::iota(0, s) | views::reverse) {
            for(i32  j : std::views::iota(0, s) | views::reverse) {
                if(i + x < s) dp[i + x][j] |= dp[i][j];
                if(j + x < s) dp[i][j + x] |= dp[i][j];
            }
        }
    }

    i64 ans = -(1L << 60);

    for(i32  i : std::views::iota(0, s)) {
        for(i32  j : std::views::iota(0, s)) {
            if(!dp[i][j]) continue;
            auto v = std::min(std::min(i, j), t - (i + j));
            if(ans < v) ans = v;
        }
    }

    std::cout << ans << "\n";
}
