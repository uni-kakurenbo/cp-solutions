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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

// 消去する → 0 で置き換える
// 操作の順番は関係ない

// segtree + dp ...?

#include "iterable/accumulate.hpp"
#include "numeric/matrix.hpp"

signed main() {
    int n, m; cin >> n >> m;
    vector<int> a(n); REP(i, n) cin >> a[i];

    Accumulate acc(ALL(a));



    return 0;
}
