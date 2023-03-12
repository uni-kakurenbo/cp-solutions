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
    string s; cin >> s;
    FOR(i, 1UL, s.size() / 2) {
        std::swap(s[i*2 - 2], s[i*2 - 1]);
    }
    print(s);
    return 0;
}
