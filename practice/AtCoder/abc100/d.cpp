/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

signed main() {
    int n, m; cin >> n >> m;
    vector<i64> x(n), y(n), z(n);
    REP(i, n) cin >> x[i] >> y[i] >> z[i];

    i64 ans = 0;

    REP(bit, 1 << 3) {
        vector<i64> v[3] = { x, y, z };
        REP(i, 3) {
            if((bit >> i) & 1) ITRR(p, v[i]) p *= -1;
        }
        debug(v);

        vector<i64> w(n);
        ITR(p, v) REP(i, n) w[i] += p[i];
        debug(w);

        sort(RALL(w));
        i64 pro = std::reduce(w.begin(), w.begin() + m);

        chmax(ans, pro);
    }

    print(ans);

    return 0;
}
