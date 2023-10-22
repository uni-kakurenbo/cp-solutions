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

#include "hash/sequence_hasher.hpp"

void solve() {
    int n; cin >> n;
    string t; cin >> t;
    valarray<string> s(n); input >> s;

    lib::sequence_hasher p(ALL(t));

    vector<int> ans;
    REP(i, n) {
        int n = t.size();
        int m = s[i].size();

        if(std::abs(n - m) >= 2) continue;

        if(n == m) {
            int cnt = 0;
            REP(j, n) cnt += s[i][j] != t[j];
            if(cnt <= 1) {
                ans.push_back(i);
            }
            continue;
        }

        debug(n, m, s[i]);

        lib::sequence_hasher q(ALL(s[i]));
        if(n < m) {
            REP(j, m) {
                if(p(0, n) == q(0, j) + q(j+1, m)) {
                    ans.push_back(i);
                    break;
                }
            }
        }
        else {
            REP(j, n) {
                if(p(0, j) + p(j+1, n) == q(0, m)) {
                    ans.push_back(i);
                    break;
                }
            }
        }
    }

    ITRR(v, ans) v++;

    print(ans.size());
    print(ans);
}
