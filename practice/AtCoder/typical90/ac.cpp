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
#include "algebraic/maximum.hpp"

using S = uni::algebraic::maximum<i32>;
S mapping(S f, S x) { return std::max(f, x); }

using action = uni::actions::mixer<S, S, mapping>;

void solve() {
    i32 w, n; input >> w >> n;

    uni::lazy_segment_tree<action> h(w, 0);

    REP(n) {
        i32 l, r; input >> l >> r; --l;
        auto nh = h(l, r).fold().val() + 1;
        h(l, r) += nh;
        print(nh);
    }
}
