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

#include "data_structure/wavelet_matrix.hpp"

void solve() {
    int n; input >> n;
    lib::wavelet_matrix wm(({
        vector<i32> v(n); input >> v;
        v;
    }));

    int q; input >> q;
    REP(q) {
        int v; input >> v;
        print(
            lib::min(
                std::abs(wm.prev(v).value_or(-INF32) - v),
                std::abs(wm.next(v).value_or(-INF32) - v)
            )
        );
    }
}
