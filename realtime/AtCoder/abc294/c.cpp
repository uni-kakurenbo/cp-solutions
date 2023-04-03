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

#include "iterable/compression.hpp"

signed main() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m); input >> a >> b;
    vector<int> c;
    std::copy(ALL(a), std::back_inserter(c));
    std::copy(ALL(b), std::back_inserter(c));

    lib::compression<int> comp(ALL(c));

    REP(i, n) print(comp.rank(a[i]) + 1);
    REP(i, m) print(comp.rank(b[i]) + 1);


    return 0;
}
