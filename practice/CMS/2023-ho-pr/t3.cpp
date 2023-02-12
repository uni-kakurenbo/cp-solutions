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
    REP(n) {
        string s; cin >> s;
        ITRR(c, s) {
            if('A' <= c and c <= 'Z') c += 'a' - 'A';
        }
        print(s);
    }
    return 0;
}
