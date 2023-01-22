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

#include "data_structure/wavelet_matrix.hpp"

signed main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m); input >> a >> b;

    lib::wavelet_matrix<int> wm(ALL(a));

    ITR(p, b) {
        int bf = wm.prev_value(p).value_or(INT_MAX);
        int af = wm.next_value(p).value_or(INT_MIN);

        int s = max(k - abs(p - bf), 0);
        int t = max(k - abs(p - af), 0);

        print(max(s, t));
    }

    return 0;
}
