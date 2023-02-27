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

#include "numeric/modint.hpp"

using mint = lib::modint998244353;

signed main() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    REP(i, n) cin >> a[i] >> b[i];

    mint ans0 = 1, ans1 = 1;
    REP(i, 1, n) {
        mint _ans0 = ans0 * (a[i] != a[i-1]) + ans1 * (a[i] != b[i-1]);
        mint _ans1 = ans0 * (b[i] != a[i-1]) + ans1 * (b[i] != b[i-1]);
        ans0 = _ans0, ans1 = _ans1;
        debug(ans0, ans1);
    }

    print(ans0 + ans1);

    return 0;
}
