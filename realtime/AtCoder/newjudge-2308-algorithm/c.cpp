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

i32 decl(i32 x) {
    print(x);
    std::cout << std::flush;
    int res; input >> res;
    return res;
}

void solve() {
    int n; cin >> n;
    lib::set<i64> st; FOR(x, 1, 2*n+1) st.insert(x);

    while(true) {
        int res = decl(st.min());
        if(res == 0) return;
        st.pop_min();
        st.remove(res);
    }
}
