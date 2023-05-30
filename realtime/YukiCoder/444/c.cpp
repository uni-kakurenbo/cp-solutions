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

void solve() {
    i64 n, m, p, q; cin >> n >> m >> p >> q;
    i64 a = m % p;

    REP(q) {
        i64 x, f; cin >> x >> f;
        debug(x, f);

        i64 t = x % p;
        if(t == 0) {
            if(f == 0) print(m);
            else print(0);
        }
        else {
            i64 v = (f * lib::inv_mod(x, p)) % p;
            debug(v);
            print(m / p + (v <= a and v%p != 0));
        }
    }
}
