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

#include "adapter/set.hpp"

signed main() {
    int q; cin >> q;

    lib::multiset<ll> st;

    REP(i, q) {
        short com; cin >> com;
        ll x; cin >> x;
        if(com == 1) st.insert(x);
        if(com == 2) {
            short k; cin >> k;
            print(st.prev(x, --k).value_or(-1));
        }
        if(com == 3) {
            short k; cin >> k;
            print(st.next(x, --k).value_or(-1));
        }
    }
    return 0;
}
