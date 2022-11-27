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

#include "numeric/boundary_seeker.hpp"

const ld EPS = numeric_limits<ld>::epsilon();

signed main() {
    ll a, b; cin >> a >> b;

    auto f = [&](ld x) -> ld {
        return b*x + a/sqrt(1 + x);
    };

    ll x = pow(a, 2.0/3) / (pow(2, 2.0/3) * pow(b, 2.0/3)) - 1;
    chmax(x, 0);

    ld ans = min({f(max(0LL,x-1)), f(x), f(x+1)});

    printf("%.20Lf", ans);

    return 0;
}
