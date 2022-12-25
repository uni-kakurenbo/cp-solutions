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

#include "grid.hpp"
using namespace Lib;

signed main() {
    int n, l; cin >> n >> l;
    Grid<int> a(n, l); a.read();

    int cur = -1, cnt = 0;
    while(true) {
        int i = mod(cnt, n);
        auto itr = upper_bound(ALL(a[i]), cur);
        if(itr == a[i].end()) {
            print(cnt);
            return 0;
        }
        cur = *itr;
        ++cnt;
    }

    return 0;
}
