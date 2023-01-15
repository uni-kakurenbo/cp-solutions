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
    constexpr ll L = 1'000'000'000'000;

    int n; cin >> n;
    vector<ll> a(n); input >> a;

    vector<ll> v(n);

    REP(i, n) v[i] = 2 * L * (i - n/2) / n;
    debug(v);

    ll sum = 0;
    REP(i, n) sum += v[i] * a[i];

    debug(sum);

    return 0;
}
