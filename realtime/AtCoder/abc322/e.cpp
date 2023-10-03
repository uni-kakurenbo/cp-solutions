/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, k, p; cin >> n >> k >> p;

    valarray<i64> C(n+1);
    lib::valgrid<int> A(n+1, 5);
    REP(i, n) {
        input >> C[i];
        REP(j, k) input >> A[i][j];
    }
    REP(i, k, 5) C[n] = 0, A[n][i] = p;
    debug(C, A);

    multi_container<i64,5> dp(p+1, p+1, p+1, p+1, p+1);
    FOR(a, p) FOR(b, p) FOR(c, p) FOR(d, p) FOR(e, p) dp[a][b][c][d][e] = INF64;
    dp[0][0][0][0][0] = 0;

    REP(i, n+1) {
        FORD(a, p) FORD(b, p) FORD(c, p) FORD(d, p) FORD(e, p) {
            chmin(
                dp(
                    lib::min(a + A[i][0], p),
                    lib::min(b + A[i][1], p),
                    lib::min(c + A[i][2], p),
                    lib::min(d + A[i][3], p),
                    lib::min(e + A[i][4], p)
                ),
                dp(a, b, c, d, e) + C[i]
            );
        }
    }

    print(lib::to_optional_if_or_over(dp(p, p, p, p, p), INF64).value_or(-1));
}
