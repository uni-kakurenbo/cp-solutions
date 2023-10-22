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
    valarray<int> w(n), x(n);
    input >> lib::views::zip(w, x);
    debug(w, x);

    auto ok = [&](int t, int i) -> bool {
        int s = x[i] + 9;
        int e = x[i] + 18;
        debug(s, t, e);
        if(s <= t and t + 1 <= e) return true;
        if(s <= t - 24 and t - 23 <= e) return true;
        if(s <= t + 24 and t + 25 <= e) return true;
        return false;
    };

    int ans = 0;
    REP(t, 48) {
        int cnt = 0;
        REP(i, n) {
            cnt += ok(t, i) * w[i];
        }
        chmax(ans, cnt);
    }

    print(ans);
}
