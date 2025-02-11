/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/lazy_segment_tree.hpp"

void solve() {
    i32 n; input >> n;
    valarray<tuple<i32, i32, i64>> dcs(n); input >> dcs;
    dcs.sort();

    i32 m = 0;
    ITR(d, c, s, dcs) chmax(m, d);

    vector<i64> dp(m + 1, -INF64), next;
    dp[0] = 0;

    ITR(d, c, s, dcs) {
        auto next = dp;

        FOR(j, m) {
            if(j < c or j > d) continue;
            chmax(next[j], dp[j - c] + s);
        }

        dp = std::move(next);
    }

    print(std::ranges::max(dp));
}
