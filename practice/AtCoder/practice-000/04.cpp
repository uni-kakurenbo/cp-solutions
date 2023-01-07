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
    vector<ll> a(n); input >> a;

    ll ans = INT64_MAX;

    REP(divis, 1 << n) {
        ll bxor = 0, bor = 0;
        REP(i, n) {
            bor |= a[i];
            if((divis & (1 << i)) or i == n-1) bxor ^= bor, bor = 0;
        }
        chmin(ans, bxor);
    }

    print(ans);

    return 0;
}
