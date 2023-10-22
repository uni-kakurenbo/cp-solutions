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
    string t; cin >> t;
    valarray<string> s(n); input >> s;

    valarray<int> front(n), back(n);
    REP(i, n) {
        int m = s[i].size();
        {
            int k = 0;
            REP(j, m) {
                if(s[i][j] == t[k]) ++k;
                if(k >= (int)t.size()) break;
            }
            front[i] = k;
        }
        {
            int k = t.size();
            REPD(j, m) {
                if(s[i][j] == t[k-1]) --k;
                if(k <= 0) break;
            }
            back[i] = k;
        }
    }
    debug(front, back);

    lib::counter cnt_front(ALL(front));
    lib::counter cnt_back(ALL(back));
    debug(cnt_front, cnt_back);

    i64 ans = 0;
    i64 sum = 0;
    FORD(i, (int)t.size()) {
        sum += cnt_front[i];
        ans += cnt_back[i] * sum;
        debug(sum);
    }

    print(ans);
}
