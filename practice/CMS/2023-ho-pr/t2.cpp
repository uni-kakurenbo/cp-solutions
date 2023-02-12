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
    int n; cin >> n;
    int ans0 = 0, ans1 = 0;
    REP(n) {
        ll a, b; cin >> a >> b;
        ans0 += a > b;
        ans1 += a < b;
    }
    print(ans0, ans1);
    return 0;
}
