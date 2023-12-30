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
    int n, q; input >> n >> q;
    valarray<i64> a(n); input >> a;
    a.sort();

    lib::segment_tree<lib::actions::range_sum<i64>> data(ALL(a));

    REP(q) {
        i64 x; input >> x;
        print(data.max_right(0, [&](auto v) { return v.val() <= x; }));
    }

}
