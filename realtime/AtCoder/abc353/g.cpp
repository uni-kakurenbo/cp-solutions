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

#include "data_structure/segment_tree.hpp"
#include "action/range_max.hpp"

void solve() {
    i64 n, c; input >> n >> c;
    i32 m; input >> m;
    vector<i64> t(m), p(m); input >> uni::views::zip(t, p);
    t -= 1;
    debug(t, p);

    uni::segment_tree<uni::actions::range_max<i64>> dp0(n, -INF64), dp1(n, -INF64);
    dp0[0] = 0;
    dp1[0] = 0;

    REP(i, m) {
        i64 l = dp0.fold(t[i], n).val() + t[i] * c;
        i64 r = dp1.fold(0, t[i]).val() - t[i] * c;
        {
            i64 next = std::max(l, r) - c * t[i];
            dp0[t[i]] += next + p[i];
        }
        {
            i64 next = std::max(l, r) + c * t[i];
            dp1[t[i]] += next + p[i];
        }
    }

    i64 ans = 0;

    REP(i, n) {
        debug(dp0[i].val().val() + i * c, dp1[i].val().val() - i * c);
        chmax(ans, dp0[i].val().val() + i * c);
        chmax(ans, dp1[i].val().val() - i * c);
    }

    print(ans);
}
