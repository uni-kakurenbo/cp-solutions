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

#include "data_structure/dynamic_sequence.hpp"
#include "data_structure/red_black_tree.hpp"
#include "action/range_add_range_sum.hpp"

void solve() {
    int n, q; input >> n >> q;
    vector<i64> x(n); input >> x;

    lib::dynamic_sequence<
        lib::actions::range_add_range_sum<i64>,
        lib::persistent_red_black_tree_context<i32>
    > data(x);

    REP(q) {
        int t; input >> t;
        if(t == 1) {
            int a, b, v; input >> a >> b >> v; --a;
            data(a, b) += v;
        }
        if(t == 2) {
            int a, b, c, d; input >> a >> b >> c >> d; --a, --c;
            data.replace(a, b, data.clone(c, d));
        }
        if(t == 3) {
            int a, b; input >> a >> b; --a;
            print(data(a, b).fold());
        }
    }
}
