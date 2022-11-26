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

size_t LIS(const std::vector<int>& v) {
    vector<int> dp;

    for (const auto& elem : v) {
        auto itr = upper_bound(dp.begin(), dp.end(), elem);
        if (itr == dp.end()) dp.push_back(elem);
        else *itr = elem;
    }

    return dp.size();
}

signed main() {
    int n; cin >> n;
    vector<int> a(n); REP(i, n) cin >> a[i];

    print(n - LIS(a));

    return 0;
}
