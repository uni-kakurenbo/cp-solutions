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

#include "iterable/compression.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a;

    lib::compression<i64> comp(ALL(a));
    valarray<i64> asleep(*std::max_element(ALL(comp)) + 2);

    valarray<i64> lef(n/2 + 2, INF64), rig(n/2 + 2, INF64);
    lef[0] = -INF64;
    rig[0] = 0;

    REP(i, 1, n) {
        if(i%2 == 1) {
            asleep[comp[i]] += a[i+1] - a[i];
            lef[i/2 + 1] = a[i];
        }
        else {
            rig[i/2] = a[i];
        }
    }
    REP(i, asleep.size()-1) asleep[i+1] += asleep[i];
    debug(asleep, lef, rig);

    int q; cin >> q;
    REP(q) {
        i64 l, r; cin >> l >> r;
        int p = std::lower_bound(ALL(lef), l) - lef.begin();
        int q = std::upper_bound(ALL(rig), r) - rig.begin() - 1;
        debug(p, q);
        i64 ans = 0;
        if(p <= q) ans += asleep[q*2-1] - asleep[p*2-2];
        debug(ans);
        if(rig[p - 1] <= r) ans += std::max(rig[p - 1] - l, 0L);
        debug(ans);
        if(lef[q + 1] >= l) ans += std::max(r - lef[q + 1], 0L);
        if(p == q+2) ans = r - l;
        debug(ans);
        print(ans);
    }
}
