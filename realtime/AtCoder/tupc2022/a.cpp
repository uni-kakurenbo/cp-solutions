/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    int n, k; std::cin >> n >> k;
    std::vector<int> p(n); input >> p;

    int smx = 0;
    REPD(i, 1, n) {
        smx = i+1;
        if(p[i] != i+1) break;
    }

    debug(smx);
    print(smx < k ? "Yes" : "No");


    return 0;
}
