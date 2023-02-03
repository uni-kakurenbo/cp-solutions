/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */


signed main() {
    int n; cin >> n;
    vector<pair<string,int>> vs(n);

    REP(i, n) {
        string s; cin >> s;
        vs[i] = { s, i };
    }

    sort(ALL(vs));
    debug(vs);

    vector<int> ans(n);
    REP(i, n) {
        auto lcp = [&](int j) -> int {
            if(j < 0 or j >= n) return 0;
            int l = max(vs[i].first.size(), vs[j].first.size());

            int res = 0;
            REP(k, l) {
                if(vs[i].first[k] != vs[j].first[k]) break;
                ++res;
            }

            return res;
        };

        ans[vs[i].second] = max(lcp(i-1), lcp(i+1));
    }

    print(ans);

    return 0;
}
