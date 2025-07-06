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

#include "template/warnings.hpp"
void solve() {
    i32 n, q; input >> n >> q;
    uni::dynamic_sequence<i64> data(n);
    REP(i, n) data[i] = i + 1;

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i32 p, x; input >> p >> x; --p;
            data[p] = x;
        }
        if(t == 2) {
            i32 p; input >> p; --p;
            print(data[p]);
        }
        if(t == 3) {
            i32 k; input >> k; k %= n;
            data.rotate_left(k);
        }
    }
}
