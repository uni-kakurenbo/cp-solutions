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
    int a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
    a *= 100, b *= 100;

    double max_d = -100;
    int ans0 = -1, ans1 = -1;

    FOR(i, 0, 30) FOR(j, 0, 30) FOR(k, 0, 3000){
        int water = a*i + b*j;
        if(water == 0) continue;

        auto validate = [&](int v) {
            int sugar = c*k + d*v;
            return sugar*100 <= water*e and water + sugar <= f;
        };

        if(not validate(0)) continue;

        BoundarySeeker<int> seeker(validate);
        int l = seeker.bound(0, 3001);
        int sugar = c*k + d*l;

        if(sugar >= 0 and chmax(max_d, (double)(sugar)/(sugar+water))) {
            ans0 = sugar + water;
            ans1 = sugar;
        };
    }

    print(ans0, ans1);

    return 0;
}
