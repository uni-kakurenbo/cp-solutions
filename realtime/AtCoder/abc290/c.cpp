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
    int n, k; cin >> n >> k;
    vector<int> a(n); input >> a;

    auto st = set(ALL(a));

    int ans = 0;
    REP(i, k) {
        if(not st.count(i)) break;
        chmax(ans, i+1);
    }

    print(ans);

    return 0;
}
