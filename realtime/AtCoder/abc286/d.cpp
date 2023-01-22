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
    int n; ll x; cin >> n >> x;
    vector<ll> a(n), b(n);
    REP(i, n) cin >> a[i] >> b[i];

    bitset<20000> bits(0);

    bits.set(0);

    REP(i, n) {
        REP(b[i]) bits |= bits << a[i];
    }

    print((bits[x] ? "Yes" : "No"));

    return 0;
}
