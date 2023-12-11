/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

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

using mint = lib::modint998244353;

void solve() {
    int n, a, b, p, q; cin >> n >> a >> b >> p >> q; --a, --b;
    mint inv_p = mint{p}.inv(), inv_q = mint{q}.inv();

    lib::multi_container<mint,3> dp(2*n + 1, n, n);

    dp[0][a][b] = 1;

    REP(k, 2 * n) {
        REP(i, a, n-1) REP(j, b, n-1) {
            if(dp[k][i][-1] != 0 and dp[k][-1][i] != 0) continue;
            if(k%2 == 0) FOR(x, 1, p) dp[k+1][std::min(n-1, i + x)][j] += dp[k][i][j] * inv_p;
            if(k%2 == 1) FOR(y, 1, q) dp[k+1][i][std::min(n-1, j + y)] += dp[k][i][j] * inv_q;
        }
        // debug(k, dp[k+1]);
    }

    mint ans = 0, r = 0;
    REP(k, 2*n) REP(i, n) ans += dp[k][-1][i];
    REP(k, 2*n) REP(i, n) r += dp[k][i][-1];

    debug(ans, r);

    print(ans);
}
