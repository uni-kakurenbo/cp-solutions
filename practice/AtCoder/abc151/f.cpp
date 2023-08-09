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

#include "geometries.hpp"

using real = ld;

using point = lib::point<real>;

void solve() {
    int n; cin >> n;
    valarray<point> ps(n); input >> ps;

    real ans = INF<real>;

    REP(i, n) REP(j, i+1, n) {
        lib::circle c(lib::segment(ps[i], ps[j]));
        if(std::isnan(c.radius())) continue;
        bool ok = std::all_of(ALL(ps), [&](auto&& p) { return c.relation(p) != lib::positional_relation::out; });
        if(ok) {
            chmin(ans, c.radius());
        }
    }

    REP(i, n) REP(j, i+1, n) REP(k, j+1, n) {
        lib::circle c(ps[i], ps[j], ps[k]);
        if(std::isnan(c.radius())) continue;
        bool ok = std::all_of(ALL(ps), [&](auto&& p) { return c.relation(p) != lib::positional_relation::out; });
        if(ok) {
            chmin(ans, c.radius());
        }
    }

    print(ans);
}
