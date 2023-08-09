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
    lib::range_extractor<valarray<i64>> a(n); input >> a;

    valarray<i64> to(n, -1);

    stack<i64> stk;
    REP(i, n) {
        if(a[i-1] + 1 == a[i]) {
            to[i] = i-1;
        }
        else if(a[i] == 1) {
            stk.push(i-1);
            to[i] = i-1;
        }
        else {
            while(not stk.empty() and a[stk.top()] != a[i] - 1) stk.pop();
            if(not stk.empty()) to[i] = stk.top(), stk.pop();
        }
    }
    debug(to);

    valarray<i64> dp(n+1);
    REPD(i, n) chmax(dp[to[i]], dp[i] + i - to[i]);
    debug(dp);

    dp += 1;
    i64 ans = 0;
    REP(i, n) if(a[i] == 1) ans += dp[i];

    print(ans);
}
