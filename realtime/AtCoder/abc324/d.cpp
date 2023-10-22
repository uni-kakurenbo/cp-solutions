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
    string s; cin >> s;
    s.sort().reverse();
    debug(s);

    int cnt = 0;

    i64 max = std::stoll(s);
    for(i64 i=0; i*i <= max; ++i) {
        string t = std::to_string(i * i);
        if(s.size() < t.size()) continue;
        t = string(s.size() - t.size(), '0') + t;
        t.sort().reverse();
        debug(t);
        if(s == t) cnt++;
    }

    print(cnt);
}
