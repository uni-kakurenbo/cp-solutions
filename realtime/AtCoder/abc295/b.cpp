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
    int r, c; cin >> r >> c;
    lib::grid<char,string> G(r, c); input >> G;

    auto H = G;

    REP(i, r) REP(j, c) {
        char v = G[i][j];
        if('0' <= v and v <= '9') {
            int s = v - '0';
            REP(p, r) REP(q, c) {
                int d = abs(i - p) + abs(j - q);
                if(d <= s) {
                    H[p][q] = '.';
                }
            }
        }
    }

    ITR(g, H) print(g);

    return 0;
}
