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
    i64 h, w; cin >> h >> w;
    if(h > w) swap(h, w);

    auto can = [&](double r) -> bool {
        if(2*r > h) return false;
        if(lib::distance<double>({r, r}, {h-r, w-r}) < 2*r) return false;
        return true;
    };

    lib::boundary_seeker<double> seeker(can);
    print(seeker.bound<false>(0));

    return 0;
}
