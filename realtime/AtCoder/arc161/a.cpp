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
    if(n == 1) {
        print("Yes");
        return;
    }
    vector<i64> a(n); input >> a;

    a.sort();

    vector<i64> b(n);
    REP(i, n) {
        b[(2*i) % n] = a[i];
    }

    bool ans = true;

    REP(i, 1, n, 2) {
        ans &= b[i-1] < b[i] and b[i] > b[i+1];
    }

    print(ans ? "Yes" : "No");
}
