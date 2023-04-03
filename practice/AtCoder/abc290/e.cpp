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
    int n; cin >> n;
    vector<int> a(n); input >> a; ITRR(v, a) v--;

    lib::multi_container<int,2> pos(n, 0);
    REP(i, n) pos[a[i]].push_back(i);
    REP(i, n) sort(ALL(pos[i]));

    i64 all = 0, good = 0;

    REP(i, n) {
        all += 1LL * (i + 1) / 2 * (n - i);
        i64 l = 0, r = pos[i].size()-1;
        while(l < r) {
            if(pos[i][l] < n - pos[i][r]) good += (r - l) * (pos[i][l] + 1), l++;
            else good += (r - l) * (n - pos[i][r]), r--;
        }
    }
    debug(all, good);

    print(all - good);

    return 0;
}
