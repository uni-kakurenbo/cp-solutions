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

i64 solve(i64 a, i64 b, i64 c) {
    i64 s = a + b + c;
    if(s%3 != 0) return -1;

    i64 t = s/3;

    if((t - a) % 2 != 0) return -1;
    if((t - b) % 2 != 0) return -1;
    if((t - c) % 2 != 0) return -1;

    i64 cnt0 = 0, cnt1 = 0;
    (a > t ? cnt0 : cnt1) += (t - a) / 2;
    (b > t ? cnt0 : cnt1) += (t - b) / 2;
    (c > t ? cnt0 : cnt1) += (t - c) / 2;
    debug(cnt0, cnt1);

    if(cnt0 + cnt1 != 0) return 0;

    return (cnt1 - cnt0) / 2;
}


signed main() {
    int $; cin >> $;
    while($--) {
        i64 a, b, c; cin >> a >> b >> c;
        print(solve(a, b, c));
    }
}
