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
    int n; cin >> n;
    valarray<int> a(n); input >> a;

    int q; cin >> q;
    std::vector<int> l(q), r(q); input >> lib::zip(l, r);
    debug(lib::zip(l, r));

    auto p = lib::concat(a, l, r);
    lib::compressed comp(ALL(p));

    valarray<i64> asleep(comp.rank_sup());
    REP(i, 1, n) {
        if(i%2) asleep[comp.rank(a[i])]++;
        else asleep[comp.rank(a[i])]--;
    }
    REP(i, 1, asleep.size()) asleep[i] += asleep[i-1];

    lib::valarray<i64> acc(asleep.size());
    REP(i, 1, asleep.size()) acc[i] = acc[i-1] + asleep[i-1] * (comp.value(i) - comp.value(i-1));

    ITR(p, q, lib::zip(l, r)) print(acc[comp.rank(q)] - acc[comp.rank(p)]);
}
