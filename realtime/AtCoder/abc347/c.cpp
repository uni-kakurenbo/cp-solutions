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
#include "action/range_affine_range_minmax.hpp"

void solve() {
    i64 n, a, b; input >> n >> a >> b;
    valarray<i64> d(n); input >> d;
    d %= (a + b);

    lib::set<i64> st;
    ITR(v, d) st.insert(v);
    debug(st);

    REP(n) {
        auto min = st.min();
        auto max = st.max();

        if(max - min < a) {
            print.yes();
            return;
        }

        st.pop_min();
        st.insert(min + (a + b));

        debug(st);
    }

    print.no();
}
