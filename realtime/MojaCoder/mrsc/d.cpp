/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    std::string s; std::cin >> s;
    int n; std::cin >> n;
    std::vector<std::string> t(n); input >> t;

    std::vector<int> g(26);
    ITR(v, s) g[v-'a']++;

    int ans = 1000000;

    REP(i, 1 << n) {
        std::vector<int> cnt(26);
        REP(b, n) {
            bool u = (i >> b) & 1;
            if(u) ITR(v, t[b]) cnt[v-'a']++;
        }
        bool f = true;
        REP(j, 26) {
            f &= cnt[j] >= g[j];
        }
        if(f) chmin(ans, __builtin_popcount(i));
    }

    print(ans == 1000000 ? -1 : ans);

    return 0;
}
