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
    int n, m; cin >> n >> m;

    vector<int> out(n);
    REP(i, m) {
        int a, b; cin >> a >> b;
        out[--a]++;
    }
    debug(out);

    vector<int> ans;
    REP(i, n) {
        if(out[i] == 0) ans.push_back(i+1);
    }

    print(ans.size());
    print(ans);

    return 0;
}
