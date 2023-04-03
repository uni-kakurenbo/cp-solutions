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

#include <atcoder/convolution>

signed main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    REP(i, n) cin >> a[i] >> b[i];

    auto conv = atcoder::convolution(a, b);
    print(0);
    REP(i, 2*n-1) print(conv[i]);

    return 0;
}
