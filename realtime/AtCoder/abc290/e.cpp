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

    map<int,ll> cnt;

    ll ans = 0;
    ll sum = 0;
    REP(i, n) {
        sum += (i+1)/2;
        debug(sum, sum - cnt[a[i]]);
        ans += sum - cnt[a[i]];
        cnt[a[i]] += (i+1)/2;
    }

    print(ans);

    return 0;
}
