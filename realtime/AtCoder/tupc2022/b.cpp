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
    i64 n, m, k; std::cin >> n >> m >> k;
    std::vector<i64> a(m), b(m);
    REP(i, m) input >> a[i] >> b[i];
    a.push_back(n+1);

    i64 ans = 0;
    i64 cur = 0;

    REP(i, m) {
        debug(a[i], b[i]);
        cur -= std::max(0L, a[i] - a[i-1]);
        chmax(cur, 0L);
        debug(cur);
        cur += b[i];
        ans += std::max(0L, std::min(cur - k, a[i+1] - a[i]));
        debug(cur, ans);
    }

    print(ans);

    return 0;
}
