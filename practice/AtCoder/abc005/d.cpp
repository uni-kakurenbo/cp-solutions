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

#include "numeric/prime.hpp"

signed main() {
    int n; cin >> n;
    lib::multi_container<i64,2> d(n, n); input >> d;
    debug(d);
    lib::accumulation_2d<i64> s(ALL(d));

    vector<i64> mx(n*n);

    FOR(i, n) FOR(j, n) FOR(k, i+1, n) FOR(l, j+1, n) {
        i64 area = (k - i) * (l - j);
        chmax(mx[area-1], s(i, j, k, l));
    }
    debug(mx);

    lib::accumulation<i64> ans(ALL(mx), 0, [](i64 a, i64 b) { return std::max(a, b); });
    debug(ans);

    int q; cin >> q;
    REP(q) {
        int p; cin >> p;
        print(ans[p]);
    }
    return 0;
}
