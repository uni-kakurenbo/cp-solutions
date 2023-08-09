/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "hash/set_hasher.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n), b(n); input >> a >> b;

    lib::set_hasher<int> s, t;
    valarray<i64> u(n), v(n);
    REP(i, n) {
        s.insert(a[i]), t.insert(b[i]);
        u[i] = s(), v[i] = t();
    }

    int q; cin >> q;
    REP(q) {
        int x, y; cin >> x >> y;
        print(u[--x] == v[--y] ? "Yes" : "No");
    }
}
