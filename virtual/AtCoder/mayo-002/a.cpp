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

signed main() {
    string s[10]; REP(i, 10) input >> s[i];

    int min_i = INF32, min_j = INF32, max_i = -INF32, max_j = -INF32;

    REP(i, 10) REP(j, 10) {
        if(s[i][j] == '.') continue;
        chmin(min_i, i), chmin(min_j, j);
        chmax(max_i, i), chmax(max_j, j);
    }

    print(++min_i, ++max_i, ++min_j, ++max_j);

    return 0;
}
