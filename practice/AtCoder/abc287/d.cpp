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
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();

    vector<int> l(m+1), r(m+1);
    l[0] = r[0] = true;
    REP(i, m) {
        l[i+1] = l[i] && (s[i] == '?' or t[i] == '?' or s[i] == t[i]);
        r[i+1] = r[i] && (s[n-i-1] == '?' or t[m-i-1] == '?' or s[n-i-1] == t[m-i-1]);
    }
    debug(l, r);

    FOR(i, m) {
        print(l[i] && r[m-i] ? "Yes" : "No");
    }

    return 0;
}
