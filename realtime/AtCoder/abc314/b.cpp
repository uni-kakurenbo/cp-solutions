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

void solve() {
    int n; cin >> n;
    lib::grid<int> a(n);
    REP(i, n) {
        int c; cin >> c;
        a[i].resize(c);
        input >> a[i];
    }

    int x; cin >> x;

    vector<i64> cands;
    REP(i, n) if(a[i].count(x) > 0) cands.push_back(i);

    if(cands.empty()) {
        print(0);
        return;
    }

    cands.sort([&](int i, int j) { return a[i].size() < a[j].size(); });
    int num = a[cands[0]].size();

    vector<i64> ans;
    REP(i, cands.size()) {
        if(a[cands[i]].size() == num) ans.push_back(cands[i]);
    }

    ans.sort();

    ITRR(v, ans) v++;

    print(ans.size());
    print(ans);
}
