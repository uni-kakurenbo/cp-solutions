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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

bool validate(
    const int ax, const int ay,
    const int bx, const int by,
    const int cx, const int cy,
    const int tx, const int ty
) {
    const int p0 = (bx - ax) * (ty - ay) - (by - ay) * (tx - ax);
    const int p1 = (cx - bx) * (ty - by) - (cy - by) * (tx - bx);
    const int p2 = (ax - cx) * (ty - cy) - (ay - cy) * (tx - cx);
    return p0 > 0 and p1 > 0 and p2 > 0) or (p0 < 0 and p1 < 0 and p2 < 0;
}

signed main() {
    int px[4], py[4];
    REP(i, 4) cin >> px[i] >> py[i];

    REP(i, 4) {
        bool valid = true;
        if(
            not validate(
                px[i%4], py[i%4],
                px[(i+1)%4], py[(i+1)%4],
                px[(i+2)%4], py[(i+2)%4],
                px[(i+3)%4], py[(i+3)%4]
            )
        ) {
            valid = false;
        }
    }

    cout << (valid ? "Yes" : "No") << ln;
}
