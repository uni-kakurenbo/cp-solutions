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

    int q; cin >> q;
    REP(q) {
        ll t, k; cin >> t >> k; --k;
        ll p = k >> min(t, 63LL);
        ll d = __builtin_popcountll(k % (1LL << min(t, 63LL)));
        print(char('A' + ((s[p] - 'A') + d + t) % 3));
    }

    return 0;
}
