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

#include "numeric/boundary_seeker.hpp"

i64 f(i64 a, i64 b) {
    return a*a*a + a*a*b + a*b*b + b*b*b;
}

signed main() {
    i64 n; cin >> n;
    i64 m = std::cbrt(n) + 1;

    i64 ans = INF64;

    FOR(a, m) {
        lib::boundary_seeker<i64> seeker([&](i64 v) { return f(a, v) >= n; });
        chmin(ans, f(a, seeker.bound_or(m, -1, m)));
    }

    print(ans);

    return 0;
}
