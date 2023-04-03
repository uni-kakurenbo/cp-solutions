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
    vector<int> a(n); input >> a;
    std::prev_permutation(ALL(a));
    print(a);
    return 0;
}
