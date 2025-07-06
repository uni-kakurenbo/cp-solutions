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

#include "data_structure/dynamic_sequence.hpp"
#include "action/range_sum.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 q; input >> q;

    uni::dynamic_sequence<uni::actions::range_sum<i64>> data;

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i64 c, x; input >> c >> x;
            data.push_back(x, c);
        }
        if(t == 2) {
            i64 k; input >> k;
            print(data(0, k).fold());
            data.pop_front(k);
        }
    }
}
