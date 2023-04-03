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

signed main() {
    int n, m; cin >> n >> m;

    vector<int> a(n, -1);

    REP(m) {
        int s, c; cin >> s >> c; --s;
        if(a[s] >= 0 and a[s] != c) {
            print(-1);
            return 0;
        }
        a[s] = c;
    }


    if(a[0] < 1 and n == 1) {
        print(0);
        return 0;
    }

    if(a[0] == 0) {
        print(-1);
        return 0;
    }

    chmax(a[0], 1);
    REP(i, 1, n) chmax(a[i], 0);

    ITR(v, a) print << v;
    print();

    return 0;
}
