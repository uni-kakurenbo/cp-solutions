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

signed main() {
    int n; cin >> n;
    vector<int> l(n); REP(i, n) cin >> l[i];
    sort(ALL(l));

    ll ans = 0;

    REPF(i, l.begin(), l.end()) {
        auto k = i + 1;
        REPF(j, i+1, l.end()) {
            while(k < l.end() and *k < *i + *j) ++k;
            ans += k - (j + 1);
        }
    }

    print(ans);
}
