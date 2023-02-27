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
    int n; cin >> n;
    string s; cin >> s;

    set<pair<int,int>> st;

    int x = 0, y = 0;
    st.emplace(x, y);
    REP(k, n) {
        if(s[k] == 'R') x++;
        if(s[k] == 'L') x--;
        if(s[k] == 'U') y++;
        if(s[k] == 'D') y--;
        if(st.count({ x, y })) {
            print("Yes");
            return 0;
        }
        st.emplace(x, y);
    }

    print("No");

    return 0;
}
