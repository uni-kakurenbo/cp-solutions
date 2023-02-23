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

ll solve(ll n, ll d, ll k) {
    --k;
    ll f = n / gcd(n, d);
    return mod(d * mod(k, f), n) + k/f;
}

signed main() {
    int $; cin >> $;
    while($--) {
        ll n, d, k; cin >> n >> d >> k;
        print(solve(n, d, k));
    }
    return 0;
}
