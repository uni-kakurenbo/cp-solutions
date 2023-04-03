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

    lib::multi_container<int,2> a(n+1, 10);
    REP(i, n) {
        char c = s[i];
        a[i+1][c-'0'] = 1;
    }

    REP(i, n) REP(j, 10) a[i+1][j] += a[i][j];
    FOR(i, n) REP(j, 10) a[i][j] %= 2;
    debug(a);

    i64 ans = 0;

    map<vector<int>,i64> cnt;
    FOR(i, n) cnt[a[i]]++;

    ITR(v, c, cnt) ans += c * (c - 1) / 2;

    debug(cnt);

    print(ans);

    return 0;
}
