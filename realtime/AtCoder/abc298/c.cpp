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
    int n, q; cin >> n >> q;

    std::vector<multiset<int>> btoc(n);
    std::vector<set<int>> ctob(200'000);

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int i, j; cin >> i >> j; --i, --j;
            ctob[i].insert(j+1);
            btoc[j].insert(i+1);
        }
        if(t == 2) {
            int i; cin >> i; --i;
            print(btoc[i]);
        }
        if(t == 3) {
            int i; cin >> i; --i;
            print(ctob[i]);
        }
    }
}
