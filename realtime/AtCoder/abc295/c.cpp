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

#include "iterable/counter.hpp"

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;

    lib::counter<int> cnt(ALL(a));

    i64 ans = 0;

    ITR(v, c, cnt) {
        ans += c / 2;
    }

    print(ans);

    return 0;
}
