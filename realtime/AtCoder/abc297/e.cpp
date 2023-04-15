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

#include "numeric/boundary_seeker.hpp"

void solve() {
    int n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;

    set<i64> p, q(ALL(a));

    while(p.size() < k) {
        i64 tp = *q.begin(); q.erase(q.begin());
        REP(i, n) q.insert(tp + a[i]);
        p.insert(tp);
    }

    print(*p.rbegin());

}
