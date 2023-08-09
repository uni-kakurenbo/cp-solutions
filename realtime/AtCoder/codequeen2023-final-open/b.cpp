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
    using point = lib::point<int>;
    valarray<point> ps(n-1); input >> ps;
    ps -= point{ 1, 1 };

    valarray<i64> a(n), b(n), c(2*n), d(2*n);
    ITR(i, j, ps) {
        a[i]++;
        b[j]++;
        c[i+j]++;
        d[i + (n-j-1)]++;
    }
    debug(a, b, c, d);

    int i = std::find(ALL(a), 0) - a.begin();
    int j = std::find(ALL(b), 0) - b.begin();
    debug(i, j);

    if(c[i+j] == 0 and d[i + (n-j-1)] == 0) print(i+1, j+1);
    else print(-1);
}
