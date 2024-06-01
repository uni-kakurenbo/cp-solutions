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

#include "template/warnings.hpp"
#include "data_structure/fenwick_tree.hpp"
#include "action/range_add_range_sum.hpp"

void solve() {
    i32 n; input >> n;
    vector<i64> ls(n), rs(n); input >> uni::views::zip(ls, rs);
    uni::compressed comp(uni::views::concat(ls, rs));

    valarray<i32> is(n); std::iota(ALL(is), 0);
    is.sort([&](i32 i, i32 j) { return std::make_pair(rs[i], ls[i]) < std::make_pair(rs[j], ls[j]); });

    ls = uni::ordered_by(ls, is), rs = uni::ordered_by(rs, is);
    debug(ls, rs);

    uni::fenwick_tree<uni::actions::range_add_range_sum<i32>> cnt(2 * n);

    i64 ans = 0;

    ITR(l, r, uni::views::zip(ls, rs)) {
        debug(comp.rank(l), comp.rank(r));
        ans += cnt(comp.rank(l), 2 * n).fold().val();
        cnt[comp.rank(r)] += 1;
        debug(cnt);
    }

    print(ans);
}
