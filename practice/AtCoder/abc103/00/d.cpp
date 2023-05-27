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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

signed main() {
    int n, m; cin >> n >> m;
    vector<pair<int,int>> h(m); REP(i, m) cin >> h[i].$F >> h[i].$S, --h[i].$F, --h[i].$S;

    sort(ALL(h), [&](auto a, auto b) { return a.$S < b.$S; });
    debug(h);

    vector<int> cut;

    int ans = 0;
    REP(i, m) {
        if(lower_bound(ALL(cut), h[i].$F) != cut.end()) continue;
        cut.push_back(h[i].$S-1);
        ++ans;
    }

    print(ans);

    return 0;
}
