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
    int h, w; cin >> h >> w;
    grid<char,string> G(h, w); input >> G;

    using mint = lib::modint1000000007;

    lib::multi_container<mint,2> p(h+1,w), q(h,w+1), r(h+1,w+1), dp(h+1,w+1);

    dp(0,0) = 1;

    REP(i, h) REP(j, w) {
        if(G(i,j) == '#') continue;
        p(i,j) = p(i-1,j) + dp(i-1,j);
        q(i,j) = q(i,j-1) + dp(i,j-1);
        r(i,j) = r(i-1,j-1) + dp(i-1,j-1);
        dp(i,j) += p(i,j) + q(i,j) + r(i,j);
    }
    debug(p, q, r, dp);

    print(dp(-2,-2));
}
