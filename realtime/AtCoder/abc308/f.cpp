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

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> p(n), l(m), d(m); input >> p >> l >> d;
    valarray<spair<i64>> ld(m);
    REP(i, m) ld[i] = { l[i], d[i] };

    std::sort(ALL(p));
    std::sort(ALL(ld), [&](auto& a, auto& b) {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
    });

    multiset<int> st(ALL(p));

    i64 used = 0;

    REP(i, m) {
        auto [ li, di ] = ld[i];
        auto itr = st.lower_bound(li);
        if(itr == st.end()) continue;
        st.erase(itr);
        used += di;
    }

    print(p.sum() - used);
}
