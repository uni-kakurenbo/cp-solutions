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

#include "data_structure/lazy_segment_tree.hpp"
#include "action/range_affine_range_sum.hpp"

using mint = lib::modint998244353;

void solve() {
    int n, m; input >> n >> m;
    valarray<i64> a(n); input >> a;
    valarray<i64> l(m), r(m), x(m);
    input >> lib::views::zip(l, r, x);
    l -= 1;

    lib::lazy_segment_tree<lib::actions::range_affine_range_sum<mint>> ex(a);

    REP(i, m) {
        mint p = mint(r[i] - l[i]).inv();
        mint q = 1 - p;
        ex(l[i], r[i]) += std::make_pair(q, p * x[i]);
    }

    print(ex);
}
