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
    ll n, a, b; cin >> n >> a >> b;
    string s; cin >> s;

    ll ans = LONG_LONG_MAX;

    REP(i, n) {
        ll cost = a * i;

        REP(j, n/2) {
            int k = (i + j) % n;
            int l = (i + (n - j - 1)) % n;
            debug(k, l, s[k], s[l]);
            cost += b * (s[k] != s[l]);
        }
        debug(cost);

        chmin(ans, cost);
    }

    print(ans);




    return 0;
}
