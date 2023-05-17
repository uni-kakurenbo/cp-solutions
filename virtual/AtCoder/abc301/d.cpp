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
    string s; cin >> s;
    i64 n; cin >> n;

    auto t = s;
    std::replace(ALL(t), '?', '0');

    i64 res = stoll(t, nullptr, 2);
    debug(t, res);
    if(res > n) {
        print(-1);
        return;
    }

    std::reverse(ALL(s));

    REPD(i, (int)s.size()) {
        if(s[i] == '?' and (res | (1LL << i)) <= n) res |= 1LL << i;
        debug(i, s[i], res);
    }

    print(res);
}
