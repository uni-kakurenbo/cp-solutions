/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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
#include "action/range_chmax_range_max.hpp"

void solve() {
    i32 w, n; input >> w >> n;
    vector<i32> ls(n), rs(n), vs(n); input >> uni::views::zip(ls, rs, vs);

    uni::lazy_segment_tree<uni::actions::range_chmax_range_max<i64>> dp(w + 3);
    dp[0] = 0;

    ITR(l, r, v, uni::views::zip(ls, rs, vs)) {
        FORD(x, w) {
            dp(uni::min(x + l, w + 1), uni::min(x + r + 1, w + 2)) += dp[x].val().val() + v;
        }
        // debug(dp);
    }

    print(uni::max(-1, dp[w].val().val()));
}
