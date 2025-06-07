/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "data_structure/lazy_segment_tree.hpp"
#include "action/range_add_range_min.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n >> m;
    uni::lazy_segment_tree<uni::actions::range_add_range_min<i64>> data(n, 0);
    REP(m) {
        i32 l, r; input >> l >> r; --l;
        data(l, r) *= 1;
    }

    print(data.fold());
}
