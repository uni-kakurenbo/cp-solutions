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

using point = lib::point<ld>;

void solve() {
    int n; cin >> n;
    valarray<point> a(n); input >> a;
    valarray<spair<ld>> args(n);
    ITR(p, b, lib::views::zip(a, args)) b = { point(p.x()-1, p.y()).argument(), point(p.x(), p.y()-1).argument() };
    debug(args);
    args.sort();

    i64 ans = 0;
    ld now = 0;
    REP(i, n) {
        if(now <= args[i].second) {
            ans++;
            now = args[i].first;
        }
    }

    print(ans);
}
