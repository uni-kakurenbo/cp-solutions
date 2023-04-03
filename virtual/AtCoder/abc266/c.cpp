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

using point = lib::point<i64>;

bool ng(point a, point b, point c, point t) {
    const i64 p = lib::cross(b, t, a);
    const i64 q = lib::cross(c, t, b);
    const i64 r = lib::cross(a, t, c);
    return (p > 0 and q > 0 and r > 0) or (p < 0 and q < 0 and r < 0);
}

signed main() {
    vector<point> ps(4); input >> ps;

    bool ok = true;
    REP(i, 4) ok &= !ng(ps[i%4], ps[(i+1)%4], ps[(i+2)%4], ps[(i+3)%4]);

    print(ok ? "Yes" : "No");
}
