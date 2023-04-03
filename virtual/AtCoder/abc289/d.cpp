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
    vector<int> a(n); input >> a;
    int m; cin >> m;
    vector<int> b(m); input >> b;
    lib::set<int> st(ALL(b));
    int x; cin >> x;

    vector<int> dp(x+1);
    dp[0] = 1;

    FOR(i, x) {
        if(st.contains(i)) continue;
        REP(j, n) {
            if(i >= a[j]) dp[i] |= dp[i - a[j]];
        }
    }

    print(dp[x] ? "Yes" : "No");

    return 0;
}
