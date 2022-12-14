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
    int n; cin >> n;
    vector<int> a(n); input >> a;

    auto p = min_element(ALL(a)), q = max_element(ALL(a));

    REP(i, n) {
        int ans = 0;
        if(i != p-a.begin()) chmax(ans, abs(a[i] - *p));
        if(i != q-a.begin()) chmax(ans, abs(a[i] - *q));
        print(ans);
    }

    return 0;
}
