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

#include "numeric/boundary_seeker.hpp"
#include "iterable/counter.hpp"

signed main() {
    int n, m; cin >> n >> m;
    vector<int> a(n); input >> a;
    lib::multiset<int> st(ALL(a));

    auto can = [cnt](i64 v) mutable -> bool {
        REP(m) {
            while(true) {
                st[i]
            }
        }
    };

    lib::boundary_seeker<i64> seeker();

    return 0;
}
