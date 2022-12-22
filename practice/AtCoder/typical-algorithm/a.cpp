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

#include "numeric/boundary_seeker.hpp"

signed main() {
    int n, k; cin >> n >> k;
    vector<int> a(n); REP(i, n) cin >> a[i];

    Lib::BoundarySeeker<int> seeker([&](auto i) { return a[i] >= k; });
    print(seeker.bound_or<true>(n-1, -1));

    return 0;
}
