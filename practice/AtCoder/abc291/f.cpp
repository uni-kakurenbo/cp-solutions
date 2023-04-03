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

    vector<int> dp0(n, INF32), dp1(n, INF32);
    dp0[0] = dp1[n-1] = 0;

    REP(i, n) {
        REP(j, m) if(s[i][j] == '1') chmin(dp0[i+j+1], dp0[i] + 1);
    }
    REPD(i, n) {
        REP(j, m) if(s[i][j] == '1') chmin(dp1[i], dp1[i+j+1] + 1);
    }
    debug(dp0, dp1);

    REP(i, 1, n-1) {
        debug(i);
        int ans = INF32;
        FOR(j, 1, std::min(i, m)) {
            FOR(k, j+1, m) {
                debug(i-j, i-j+k);
                if(s[i-j][k-1] == '0') continue;
                chmin(ans, dp0[i-j] + dp1[i-j+k] + 1);
            }
        }
        print(ans == INF32 ? -1 : ans);
    }

    return 0;
}
