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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/range_add_range_min.hpp"

signed main() {
    int n; cin >> n;
    vector<i64> c(n); input >> c;

    lib::lazy_segment_tree<lib::actions::range_add_range_min<i64>> c_ev((n+1)/2);
    lib::lazy_segment_tree<lib::actions::range_add_range_min<i64>> c_odd(n/2);

    REP(i, n) {
        if(i%2 == 0) c_ev.set(i/2, c[i]);
        else c_odd.set(i/2, c[i]);
    }

    debug(c, c_ev, c_odd);

    i64 ans = 0;

    int q; cin >> q;
    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int x, a; cin >> x >> a; --x;

            i64 now;
            if(x%2 == 0) now = c_ev[x/2];
            else now = c_odd[x/2];

            if(now < a) continue;

            ans += a;

            if(x%2 == 0) c_ev.add(x/2, -a);
            else c_odd.add(x/2, -a);
        }
        if(t == 2) {
            int a; cin >> a;

            i64 now = c_ev.prod();
            if(now < a) continue;

            ans += a * c_ev.size();

            c_ev.add(-a);
        }
        if(t == 3) {
            int a; cin >> a;

            i64 now = std::min(c_ev.prod(), c_odd.prod());
            if(now < a) continue;

            ans += a * n;

            c_odd.add(-a);
            c_ev.add(-a);
        }

        debug(c_ev, c_odd);
    }

    print(ans);

    return 0;
}
