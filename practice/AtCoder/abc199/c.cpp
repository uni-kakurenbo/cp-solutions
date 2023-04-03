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

#include "view.hpp"

signed main() {
    int n; cin >> n;
    string s; cin >> s;
    lib::cyclic_view v(&s);
    int q; cin >> q;

    REP(q) {
        int t, a, b; cin >> t >> a >> b; --a, --b;
        if(t == 1) {
            swap(v[a], v[b]);
        }
        if(t == 2) {
            v.shift(n);
        }
    }

    ITR(x, v) print << x;
    print();

    return 0;
}
