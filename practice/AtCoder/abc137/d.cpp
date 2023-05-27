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
    vector<spair<int>> ps(n); input >> ps;

    std::sort(RALL(ps));

    i64 ans = 0;

    priority_queue<int> cands;
    REP(i, m) {
        while(not ps.empty() and ps.back().first <= i+1) cands.push(ps.back().second), ps.pop_back();
        if(not cands.empty()) ans += cands.top(), cands.pop();
    }

    print(ans);
}
