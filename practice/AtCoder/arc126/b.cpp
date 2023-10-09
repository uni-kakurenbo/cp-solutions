/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/wavelet_matrix.hpp"

void solve() {
    int n, m; cin >> n >> m;
    valarray<lib::point<int>> ps(m); input >> ps;
    ps -= lib::point<int>{ 1, 1 };
    debug(ps);

    lib::valarray<int> ix(n, INF32), iy(n, INF32);
    lib::valarray<int> rx(n, -1), ry(n, -1);
    REP(i, m) {
        if(chmin(ix[ps[i].x()], ps[i].y())) rx[ps[i].x()] = i;
        if(chmin(iy[ps[i].y()], ps[i].x())) ry[ps[i].y()] = i;
    }
    lib::wavelet_matrix<int> xx(ALL(ix)), yy(ALL(iy));
    debug(ix, iy);

    lib::graph<int> G(m);
    REP(i, m) {
        {
            auto v = xx(ps[i].x() + 1, n).next_element(ps[i].y() + 1);
            debug(i, ps[i], v - xx.begin(), rx[v - xx.begin()]);
            if(v != xx.end()) G.add_edge(i, rx[v - xx.begin()]);
        }
        {
            auto v = yy(ps[i].y() + 1, n).next_element(ps[i].x() + 1);
            debug(i, ps[i], v - yy.begin(), ry[v - yy.begin()]);
            if(v != yy.end()) G.add_edge(i, ry[v - yy.begin()]);
        }
    }
    debug(G);

    valarray<i64> dp(m, 1);
    REP(i, n) ITR(v, G[i]) chmax(dp[v], dp[i] + 1);

    print(dp.max());
}
