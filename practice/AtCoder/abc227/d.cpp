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
    int n, k; cin >> n >> k;
    vector<i64> a(n); input >> a;

    auto can = [&](i64 p) {
        i64 sum = accumulate(ALL(a), 0LL, [&](i64 acc, i64 v) { return acc + std::min(v, p); });
        return sum >= p * k;
    };

    lib::boundary_seeker<i64> seeker(can);
    print(seeker.bound(0));

    return 0;
}
