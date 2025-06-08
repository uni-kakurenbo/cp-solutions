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

#include "template/warnings.hpp"
void solve() {
    i32 q; input >> q;

    std::stack<i32> stk;
    REP(100) stk.push(0);

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i32 x; input >> x;
            stk.push(x);
        }
        if(t == 2) {
            print(stk.top());
            stk.pop();
        }
    }
}
