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

signed main() {
    int n, m, q; cin >> n >> m >> q;

    lib::multi_container<int,2> ps(n, n);
    REP(m) {
        int l, r; cin >> l >> r; --l, --r;
        ps[l][r]++;
    }
    debug(ps);

    lib::accumulation_2d<int> cnt(ALL(ps));

    debug(cnt);

    REP(q) {
        int p, q; cin >> p >> q; --p;
        print(cnt({ p, 0 }, { n, q }));
    }

    return 0;
}
