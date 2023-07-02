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
    int q; cin >> q;

    multiset<int> st;
    multiset<int> ans;

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int x; cin >> x;
            auto itr = st.insert(x);

            if(itr != st.end() and itr != st.begin()) ans.remove(*std::prev(itr) ^ *std::next(itr));
            if(itr != st.begin()) ans.insert(x ^ *std::prev(itr));{
            if(std::next(itr) != st.end()) ans.insert(x ^ *std::next(itr));}
        }
        if(t == 2) {
            int x; cin >> x;
            auto itr = *st.remove(x);

            if(itr != st.end()) ans.remove(x ^ *itr);
            if(itr != st.begin()) ans.remove(x ^ *std::prev(itr));
            if(itr != st.end() and itr != st.begin()) ans.insert(*itr ^ *std::prev(itr));
        }
        if(t == 3) {
            print(*ans.begin());
        }
        debug(st, ans);
    }

    return;
}
