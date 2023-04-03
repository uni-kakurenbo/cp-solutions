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
    int x, y; char d; cin >> x >> d >> y;
    debug(x, y);
    if(y <= 2) {
        print(to_string(x) + "-"s);
        return 0;
    }
    if(y <= 6) {
        print(x);
        return 0;
    }
    if(y <= 9) {
        print(char(x + '0') + "+"s);
        return 0;
    }
    return 0;
}
