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
    int h, w; cin >> h >> w;
    lib::grid<int> G(h, w); G.read();

    REP(i, h) {
        string res;
        REP(j, w) {
            if(G[i][j] <= 0) res += '.';
            else res += G[i][j] - 1 + 'A';
        }
        print(res);
    }

    return 0;
}
