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

#include "iterable/counter.hpp"

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    lib::counter<char> cnt(ALL(s));
    debug(cnt);

    i64 ans = 1L * cnt['R'] * cnt['G'] * cnt['B'];

    REP(i, n) REP(j, i+1, n) {
        int k = 2 * j - i;
        if(j >= k or k >= n) continue;
        if(s[i] == s[j] or s[j] == s[k] or s[k] == s[i]) continue;
        debug(i, j, k);
        ans--;
    }

    print(ans);
}
