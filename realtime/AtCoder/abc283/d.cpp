/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    string s; cin >> s;
    int n = s.size();

    stack<char> stk;
    array<bool,26> al; al.fill(false);

    REP(i, n) {
        debug(al);
        if(s[i] == ')') {
            char t;
            while(true) {
                t = stk.top(); stk.pop();
                if(t == '(') break;
                al[t-'a'] = false;
            }
            continue;
        }
        if(s[i] != '(') {
            debug(i, s[i]);
            if(al[s[i]-'a']) {
                print("No");
                return 0;
            }
            al[s[i]-'a'] = true;
        }
        stk.push(s[i]);
    }

    print("Yes");

    return 0;
}
