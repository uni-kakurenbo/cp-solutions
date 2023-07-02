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
    int n, m; cin >> n >> m;
    valarray<std::string> c(n), d(m);
    valarray<i64> p(m + 1);
    input >> c >> d >> p;

    map<std::string,int> mp;
    REP(i, m) mp[d[i]] = p[i+1];

    debug(mp);

    i64 ans = 0;

    ITR(v, c) {
        if(mp.count(v)) {
            ans += mp[v];
        }
        else {
            ans += p[0];
        }
    }

    print(ans);
}
