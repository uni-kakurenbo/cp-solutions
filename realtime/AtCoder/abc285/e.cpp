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

#include "utility/applier.hpp"
#include "iterable/accumulation.hpp"

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;
    lib::accumulation<ll> acc_a(ALL(a));

    lib::maximum<ll> ans = 0;

    FOR(rest, 1, n) {
        ll cur = acc_a[(n-rest)/2] * 2;
        if((n-rest)%2) cur += a[(n-rest)/2];

        int tp = (n-rest)/2;
        if((n-rest)%2) tp = (n-rest)/2 + 1;

        debug(rest, (n-rest)/2, cur, tp);

        if(rest == 1) continue;

        ans <<= cur;

        REP(i, n/rest) {
            cur += a[i];
            cur -= a[--tp];

            debug(cur);

            ans <<= cur;
        }
    }

    print(ans);

    return 0;
}
