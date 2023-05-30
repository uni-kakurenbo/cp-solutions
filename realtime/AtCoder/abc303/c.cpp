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
    int n, m, h, k; cin >> n >> m >> h >> k;
    string s; cin >> s;
    set<spair<int>> items;
    REP(m) {
        int x, y; cin >> x >> y;
        items.emplace(x, y);
    }
    debug(items);

    int p = h;
    int x = 0, y = 0;
    REP(i, n) {
        int v = s[i];
        if(v == 'R') x++;
        if(v == 'L') x--;
        if(v == 'U') y++;
        if(v == 'D') y--;
        p--;
        if(p < 0) {
            print("No");
            return;
        }

        if(items.contains({ x, y }) and p < k) {
            p = k;
            items.remove({ x, y });
        }
    }

    print("Yes");
}
