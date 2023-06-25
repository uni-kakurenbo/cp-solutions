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

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    stack<char> stk;
    int cnt = 0;

    REP(i, n) {
        char v = s[i];

        if(v == ')') {
            if(cnt > 0) {
                while(stk.top() != '(') stk.pop();
                stk.pop(), cnt--;
                continue;
            }
        }
        if(v == '(') cnt++;

        stk.push(v);
    }

    vector<char> ans;
    while(!stk.empty()) ans.push_back(stk.top()), stk.pop();

    debug(ans);
    print(lib::join(lib::reversed(ans)));
}
