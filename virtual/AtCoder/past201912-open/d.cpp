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
    int n; cin >> n;
    vector<int> a(n); input >> a;
    sort(ALL(a));

    int mex = 0, dup = 0;
    REP(i, n) {
        if(i != 0 and a[i-1] == a[i]) {
            dup = a[i];
        }
    }

    unique(ALL(a));
    REP(i, n) {
        if(a[i] != i+1) {
            mex = i+1;
            break;
        }
    }

    if(mex == 0) {
        print("Correct");
        return 0;
    }

    print(dup, mex);

    return 0;
}
