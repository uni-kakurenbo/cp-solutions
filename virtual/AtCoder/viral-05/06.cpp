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

signed main() {
    int n; cin >> n;
    valarray<ll> a(0LL, n), b(0LL, n);
    REP(i, n) cin >> a[i];
    REP(i, n) cin >> b[i];

    ll times = b.sum() - a.sum();
    debug(times);

    valarray<ll> diff = b - a;
    // debug(diff);
    ll positive = 0, negative = 0;
    ITR(d, diff) {
        if(d > 0) positive += (d+1)/2;
        else negative += -d;
    }
    print(max(positive, negative) <= times ? "Yes" :"No");

    return 0;
}
