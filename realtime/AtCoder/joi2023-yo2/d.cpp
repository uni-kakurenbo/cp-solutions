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

signed main() {
    int n, w, d; cin >> n >> w >> d;
    vector<int> a(n-1); input >> a;

    int cnt = 0, ans = 0;
    REP(i, n-1) {
        cnt += a[i];
        if(cnt > w) {
            d -= i+1;
            if(d >= 0) ans += cnt;
            cnt = 0;
        }
        if(d < 0) {
            print(ans);
            return 0;
        }
        d -= 1;
    }
    print(ans);

    return 0;
}
