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

map<i64,i64> ans;

void test(i64 k) {
    string s = to_string(k);

    i64 g = 0;

    sort(ALL(s));
    do {
        g = gcd(g, stoll(s));
    } while(next_permutation(ALL(s)));

    if(g != k and ans.count(g) == 0) ans[g] = k;
}


signed main() {
    REP(k, 1000000) {
        test(k);
    }
    debug(ans);
}
