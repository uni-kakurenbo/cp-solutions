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
    reverse(ALL(s));

    ll ans = 0;

    ll d = 1;
    ITR(c, s) {
        ans += (c - 'A' + 1) * d;
        d *= 26;
    }

    print(ans);

    return 0;
}
