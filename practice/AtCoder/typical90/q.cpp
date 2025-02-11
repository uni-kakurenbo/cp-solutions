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

#include "data_structure/fenwick_tree.hpp"
#include "action/range_sum.hpp"
#include "adaptor/auto_expander.hpp"

void solve() {
    i32 n, m; input >> n >> m;
    vector<i32> ls(m), rs(m); input >> uni::views::zip(ls, rs);
    ls -= 1, rs -= 1;

    uni::counter<i32, uni::auto_expander<vector<i32>>> cnt_l(ls), cnt_r(rs);

    i64 ans = uni::comb(m, 2L);
    REP(i, n) ans -= uni::comb(cnt_l[i] + cnt_r[i], 2);

    uni::accumulation<i32, uni::auto_expander<vector<i32>>> cum_cnt_r(cnt_r);

    ITR(l, ls) ans -= cum_cnt_r[l];

    vector<i32> inds(m); std::iota(ALL(inds), 0);
    inds.sort([&](i32 i, i32 j) { return make_pair(rs[i], ls[i]) < make_pair(rs[j], ls[j]); });
    ls = uni::ordered_by(ls, inds), rs = uni::ordered_by(rs, inds);

    uni::fenwick_tree<uni::actions::range_sum<i32>> cnt(n);

    ITR(l, r, uni::views::zip(ls, rs)) {
        ans -= cnt(l + 1, r).fold().val();
        cnt[l] += 1;
    }

    print(ans);
}
