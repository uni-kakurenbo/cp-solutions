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

#include "hash/set_hasher.hpp"

signed main() {

    int n; cin >> n;
    lib::set_hasher<i64> a, b;

    vector<int> p(n), q(n);
    REP(i, n) {
        int v; cin >> v;
        a.insert(v);
        p[i] = a();
    }
    REP(i, n) {
        int v; cin >> v;
        b.insert(v);
        q[i] = b();
    }

    int t; cin >> t;
    REP(t) {
        int x, y; cin >> x >> y; --x, --y;
        print(p[x] == q[y] ? "Yes" : "No");
    }

    return 0;
}
