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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/segment_tree.hpp"
#include "action/range_set_range_sum.hpp"
#include "action/range_max.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i64> h(n); input >> h;

    uni::segment_tree<uni::actions::range_max<i32>> max(h);
    uni::lazy_segment_tree<uni::actions::range_set_range_sum<i64>> data(n);


    REP(i, n) {
        auto left = max.min_left(i, [&](auto v) { return v <= h[i]; });
        debug(left);
        data(left, i + 1) *= h[i];
        print(data(0, i + 1).fold() + 1);
        debug(data);
    }
}
