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

#include <atcoder/modint>

using mint = atcoder::modint998244353;

mint nCr(ll n, ll r) {
    if (n < r || n == 0) return 0;
    mint a = 1, b = 1;
    if (n < r * 2) r = n - r;
    REP(i, r) a *= n - i, b *= r - i;
    return a / b;
}

signed main() {
    mint n, m, k; input >> n >> m >> k;

    print(m.pow(n.val()));

    return 0;
}
