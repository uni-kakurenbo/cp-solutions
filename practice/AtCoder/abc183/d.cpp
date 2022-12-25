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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "data_structure/range_add.hpp"
#include "utility/applier.hpp"

signed main() {
    int n, w; cin >> n >> w;

    Lib::RangeAdd<ll> sum(200000);

    REP(i, n) {
        int s, t, p; cin >> s >> t >> p;
        sum.add(s, t, p);
    }

    Max<ll> ans = 0;
    REP(i, n) ans <<= sum.get(i);

    debug(ans);
    print(ans.val() <= w ? "Yes" : "No");

    return 0;
}
