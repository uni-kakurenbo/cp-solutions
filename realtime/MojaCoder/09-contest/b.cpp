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

#include "numeric/prime.hpp"

signed main() {
    i64 a, b, c, d, x; cin >> a >> b >> c >> d >> x;

    auto p = lib::divisors(a), q = lib::divisors(b), r = lib::divisors(c), s = lib::divisors(d);

    ll ans = 0;

    map<i64,i64> cnt;

    ITR(d0, r) ITR(d1, s) cnt[d0 + d1]++;

    ITR(d0, p) ITR(d1, q) {
        ans += cnt[x - (d0 + d1)];
    }

    print(ans);

    return 0;
}
