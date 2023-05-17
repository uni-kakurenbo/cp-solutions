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
    string s, t; cin >> s >> t;

    string atcoder = "atcoder";
    set<char> ok(ALL(atcoder));

    lib::counter<char> s_cnt(ALL(s)), t_cnt(ALL(t));
    debug(s_cnt, t_cnt);

    for(auto [ x, _ ] : s_cnt + t_cnt) {
        if(x == '@') continue;
        if(s_cnt[x] == t_cnt[x]) continue;
        if(!ok.contains(x)) {
            print("No");
            return;
        }
        if(s_cnt[x] < t_cnt[x]) s_cnt['@'] -= t_cnt[x] - s_cnt[x];
        if(t_cnt[x] < s_cnt[x]) t_cnt['@'] -= s_cnt[x] - t_cnt[x];
        if(s_cnt['@'] < 0 or t_cnt['@'] < 0) {
            print("No");
            return;
        }
    }

    debug(s_cnt, t_cnt);

    if(s_cnt['@'] != t_cnt['@']) {
        print("No");
        return;
    }


    print("Yes");
}
