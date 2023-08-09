/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/restorable_stack.hpp"

void solve() {
    int q; cin >> q;
    lib::restorable_stack<int> stk;
    REP(q) {
        string t; cin >> t;
        if(t == "ADD") {
            int x; cin >> x;
            stk.push(x);
        }
        if(t == "DELETE") {
            if(not stk.empty()) stk.pop();
        }
        if(t == "SAVE") {
            int x; cin >> x;
            stk.save(x);
        }
        if(t == "LOAD") {
            int x; cin >> x;
            if(stk.stored(x)) stk.load(x);
            else stk.clear();
        }
        print(stk.top_or(-1));
    }
}
