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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/segment_tree.hpp"
#include "action/range_sum.hpp"

void solve() {
    int n, m, q; input >> n >> m >> q;
    valarray<i64> p(n), a(n); input >> lib::views::zip(p, a);
    a -= 1;

    valarray<vector<tuple<int,int,int>>> lr(m);
    REP(i, q) {
        int t, l, r; input >> t >> l >> r; --t, --l;
        lr[t].emplace_back(i, l, r);
    }

    lib::inverse inv_a(ALL(a));
    lib::segment_tree<lib::actions::range_sum<i64>> costs(p);

    valarray<i64> ans(q);

    REP(t, m) {
        ITR(i, inv_a[t]) costs[i] += -p[i] / 2;
        ITR(i, l, r, lr[t]) {
            ans[i] = costs(l, r).fold().val();
        }
        ITR(i, inv_a[t]) costs[i] += p[i] / 2;
        debug(costs);
    }

    print(ans);
}
