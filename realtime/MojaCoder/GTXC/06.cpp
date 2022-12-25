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

#include "graph.hpp"
#include "graph/topological_sort.hpp"

signed main() {
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    REP(i, n) {
        int l; cin >> l;
        vector<int> row(l); input >> row;
        a[i] = { min(row[0], *row.rbegin()), max(row[0], *row.rbegin()) };
    }
    sort(ALL(a));
    debug(a);

    bool flag = true;
    REP(i, n-1) flag &= a[i].$S <= a[i+1].$F;

    print(flag ? "Yes" : "No");

    return 0;
}
