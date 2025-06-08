/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "data_structure/segment_tree.hpp"
#include "action/range_max.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n, d, r; input >> n >> d >> r;
    vector<i64> h(n); input >> h; h -= 1;
    uni::inverse inv(h);

    vector<i64> dp(n, 0);
    uni::segment_tree<uni::actions::range_max<i64>> seg(n);

    debug(h, inv);

    REP(i, n) {
        auto p = inv[i][0];
        if(i >= d) seg[inv[i - d][0]] = dp[inv[i - d][0]];
        chmax(dp[p], seg(uni::max(p - r, 0), uni::min(p + r + 1, n)).fold().val() + 1);
        debug(dp, seg);
    }

    print(dp.max());
}
