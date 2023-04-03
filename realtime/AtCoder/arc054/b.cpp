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

#include "numeric/extremum_seeker.hpp"

signed main() {
    ld p; cin >> p;

    auto f = [&](ld t) {
        return p * std::pow(2, t / -1.5) + t;
    };

    lib::extremum_seeker<ld,ld> seeker(f);
    debug(seeker.arg_min(0));
    print(seeker.min(0));

    return 0;
}
