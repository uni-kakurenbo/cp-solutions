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
    vector<ll> p(n); input >> p;

    set<ll> st;

    REP(i, n) REP(j, i, n) {
        st.insert(p[i]);
        st.insert(p[i] + p[j]);
    }
    debug(st);

    ll ans = 0;

    ITR(v, st) {
        debug(v);
        auto itr = st.upper_bound(m - v);
        if(itr == st.begin()) continue;
        --itr;
        chmax(ans, v + *itr);
    }

    print(ans);

    return 0;
}
