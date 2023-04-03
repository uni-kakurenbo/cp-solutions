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

signed main() {
    int q; cin >> q;

    priority_queue<i64,vector<i64>,greater<i64>> balls;
    i64 base = 0;

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            i64 x; cin >> x;
            balls.push(x - base);
        }
        if(t == 2) {
            i64 x; cin >> x;
            base += x;
        }
        if(t == 3) {
            i64 x = balls.top(); balls.pop();
            print(x + base);
        }
    }

    return 0;
}
