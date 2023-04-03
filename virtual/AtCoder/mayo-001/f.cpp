/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

signed main() {
    using mint = modint1000000007;

    int n; cin >> n;
    vector<int> a(n); input >> a;
    sort(ALL(a));

    mint ans = 0;

    REP(i, n) ans += mint{a[i]} * (n - i + 1);
    ans *= mint{4}.pow(n - 1);

    print(ans);

    return 0;
}
