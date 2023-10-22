/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/helper.hpp"
#include "data_structure/range_action/range_add_range_sum.hpp"

int op(int u, int v) { return u + v; }
int e() { return 0; }
int mapping(int f, int v) { return f == -1 ? v : f; }
int composition(int f, int g) { return f == -1 ? g : f; }
int id() { return -1; }

void solve() {
    int n, q; std::cin >> n >> q;

    using action = lib::actions::helper<int,op,e,int,mapping,composition,id>;
    using segtree = lib::lazy_segment_tree<action>;

    segtree bound[2];
    bound[0] = bound[1] = segtree(n, n - 1);
    int min[2] = { n - 1, n - 1 };

    long ans = 1LL * (n - 2) * (n - 2);
    for(int _ : std::views::iota(0, q)) {
        std::ignore = _;
        int t, x; std::cin >> t >> x; --t, --x;
        int r = bound[t][x].val().val();
        debug(r);
        ans -= r- 1;
        if(x < min[t]) bound[!t](0, r) <<= x;
        min[t] = std::min(min[t], x);
    }

    std::cout << ans << "\n";
}
