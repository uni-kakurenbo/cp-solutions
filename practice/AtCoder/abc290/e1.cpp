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

#include "iterable/counter.hpp"

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a; ITRR(v, a) v--;

    vector<int> cnt(n); ITR(v, a) cnt[v]++;

    i64 ans = 0;
    REP(i, (n+1)/2) {
        int u = a[i], v = a[n-i-1];
        ans += (n - 2*i - cnt[u]) * (i+1L);
        ans += (n - 2*i - cnt[v]) * (i+1L);
        ans -= (u != v) * (i+1);
        cnt[u]--, cnt[v]--;
    }

    print(ans);

    return 0;
}
