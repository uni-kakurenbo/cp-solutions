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

signed main() {
    i64 a, b, c; cin >> a >> b >> c;

    auto f = [&](ld t) {
        return 1.0 * a * t + b * sin(c * M_PI * t) < 100;
    };

    lib::boundary_seeker<ld> seeker(f);
    print(seeker.bound(0));

    return 0;
}
