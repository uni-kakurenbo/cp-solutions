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

signed main() {
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    a *= 100, b *= 100;

    ld mx = -1;
    pair<int,int> ans = { -1, -1 };
    FOR(i, 0, 30) FOR(j, 0, 30) {
        int water = a*i + b*j;
        if(water == 0) continue;
        FOR(k, 0, 3000) {
            auto valid = [&](int x) -> bool {
                int sugar = c*k + d*x;
                return (water + sugar <= f) and (sugar*100 <= e*water);
            };
            if(not valid(0)) continue;

            Lib::BoundarySeeker<int> seeker(valid);
            int l = seeker.bound_or(0, 3001, 0);

            int sugar = c*k + d*l;
            if(sugar >= 0 and chmax(mx, (ld)sugar/(sugar + water))) {
                ans = { sugar + water, sugar };
            }
        }
    }

    print(ans);

    return 0;
}
