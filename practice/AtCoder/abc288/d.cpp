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
    int n, k; cin >> n >> k;
    vector<ll> a(n); input >> a;

    vector sum(k, vector<ll>(n+1));
    REP(i, n) REP(j, k) sum[j][i+1] = sum[j][i] + (i%k == j ? a[i] : 0);
    debug(sum);

    int q; cin >> q;
    REP(q) {
        int l, r; cin >> l >> r; --l;
        ll st = sum[0][r] - sum[0][l];
        debug(st);
        print(all_of(ALL(sum), [&](const auto& s) { return s[r] - s[l] == st; }) ? "Yes" : "No");
    }

    return 0;
}
