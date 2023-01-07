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
    ll x_max = INT64_MIN, x_min = INT64_MAX, y_max = INT64_MIN, y_min = INT64_MAX;
    REP(n) {
        int x, y; cin >> x >> y;
        chmax(x_max, x+y); chmax(y_max, x-y);
        chmin(x_min, x+y); chmin(y_min, x-y);
    }

    print(max(x_max - x_min, y_max - y_min));

    return 0;
}
