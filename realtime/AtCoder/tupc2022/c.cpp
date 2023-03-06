/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    int h, w, n; std::cin >> h >> w >> n;

    int ans = 0;

    std::set<int> x1, y1, x2, y2, x4, y4;
    REP(n) {
        int x, y; std::cin >> x >> y;
        if(
            auto ix = x1.lower_bound(x), iy = y1.lower_bound(y);
            ix != x1.end() and iy != y1.end()
        ) {
            ans++;
        }
        x4.insert(x), y4.insert(y);
        x2.insert(x), y2.insert(y+1);
        x2.insert(x+1), y2.insert(y);
        x1.insert(x+1), y1.insert(y+1);
    }

    print(ans);

    return 0;
}
