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
    int n, k, x; cin >> n >> k >> x;
    vector<i64> a(n); input >> a;
    sort(RALL(a));

    ll ans = 0;
    REP(i, n) ans += a[i];
    REP(i, n) {
        ll take = a[i]/x;
        chmin(take, k);
        a[i] -= x * take;
        ans -= x * take;
        k -= take;
    }

    sort(RALL(a));
    REP(i, n) {
        if(k <= 0) break;
        ans -= a[i];
        --k;
    }

    print(ans);

    return 0;
}
