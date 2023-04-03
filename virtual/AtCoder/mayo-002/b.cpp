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
    int n; cin >> n;
    vector<int> a(n); input >> a; ITRR(v, a) --v;

    i64 cnt0 = 0, cnt1 = 0;

    REP(i, n) {
        int v = a[i];
        if(v == i) cnt0++;
        else if(a[v] == i) cnt1++;
    }
    debug(cnt0, cnt1);

    print(nCr(cnt0, 2L) + cnt1/2);

    return 0;
}
