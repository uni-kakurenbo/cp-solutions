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

i64 solve(const i64 x) {
    string s = to_string(x);
    if(set(ALL(s)).size() == 1) return x;

    return -1;
}

signed main() {
    int $; cin >> $;
    REP($) {
        i64 k; cin >> k;
        print(solve(k));
    }
    return 0;
}
