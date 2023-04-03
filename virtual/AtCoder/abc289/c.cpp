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
    vector<lib::set<int>> a(m);
    REP(i, m) {
        int c; cin >> c;
        REP(c) {
            int v; cin >> v;
            a[i].insert(v);
        }
    }

    int ans = 0;
    REP(p, 1 << m) {
        lib::set<int> st;
        REP(i, m) if((p >> i) & 1) st.insert(ALL(a[i]));
        debug(st);
        if(st.size() == n) ans++;
    }

    print(ans);

    return 0;
}
