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
    vector<int> a(n), b(n); input >> a >> b;

    lib::valarray<i32> ans(n);
    REP(d, 5) {
        vector<int> p(2*n), q(n);
        REP(i, 2*n) p[i] = !((a[mod(i,n)] >> d) & 1);
        REP(i, n) q[i] = !((b[n-i-1] >> d) & 1);
        auto r = atcoder::convolution(p, q);
        REP(i, n) ans[i] += (n-r[n+i-1]) << d;
    }

    print(ans.max());

    return 0;
}
