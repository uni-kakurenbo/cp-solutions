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
    int n, m; cin >> n >> m;
    lib::graph<int> G(n); G.read_bidirectionally(m);
    string s; cin >> s;

    lib::unordered_map<char,lib::set<int>> inv;
    REP(i, n) inv[s[i]].insert(i);

    i64 ans = 0;

    ITR(j, inv['G']) {
        i64 cnt_i = 0, cnt_k = 0;
        ITR(i, G[j]) {
            if(inv['R'].contains(i)) cnt_i++;
            if(inv['B'].contains(i)) cnt_k++;
        }
        debug(cnt_i, cnt_k);
        ans += cnt_i * cnt_k;
    }

    print(ans);
}
