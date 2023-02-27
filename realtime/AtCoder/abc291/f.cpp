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
    int n, m; cin >> n >> m;
    vector<string> s(n); input >> s;

    vector<ll> ans(n);

    vector<std::map<int,int>> dp(n+1);
    dp[0][0] = 1;
    REP(i, n) {
        map<int,int> nxt;
        ITR(v, c, dp[i]) {
            REP(j, m) {
                if(s[v][j] == '1') nxt[v+j+1] += c;
            }
        }
        debug(nxt);
        dp[i+1] = nxt;
    }

    REP(k, 1, n-1) {
        
    }

    return 0;
}
