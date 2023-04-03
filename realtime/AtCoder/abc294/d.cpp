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
    int n, q; cin >> n >> q;

    lib::set<int> ready, called;

    REP(i, n) ready.insert(i);

    REP(q) {
        int c; cin >> c;
        debug(ready, called);
        if(c == 1) {
            called.insert(*ready.begin());
            ready.erase(ready.begin());
        }
        if(c == 2) {
            int x; cin >> x; --x;
            called.remove(x);
        }
        if(c == 3) {
            print(*called.begin() + 1);
        }
    }
    return 0;
}
