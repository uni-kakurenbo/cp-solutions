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

void solve() {
    int n, d; input >> n >> d;
    lib::grid<int> G(d, n); input >> G;

    lib::valgrid<i64> dp(n + 1, 4, INF64);
    dp[0][0] = 0;

    REP(k, d) {
        lib::valgrid<i64> nxt(n + 1, 4, INF64);

        i64 min = INF64;
        REP(i, n) FOR(x, 3) {
            chmin(min, dp[i][x]);
        }
        REP(i, n) chmin(nxt[i][1], min + G[k][i]);

        REP(i, n) FOR(x, 3) {
            int cost = G[k][i];
            if(x == 1) cost = cost * 9 / 10;
            if(x >= 2) cost = cost * 7 / 10;
            chmin(nxt[i][std::min(3, x + 1)], dp[i][x] + cost);
        }

        debug(nxt);
        dp = std::move(nxt);
    }

    i64 ans = INF64;
    FOR(i, n) FOR(x, 3) chmin(ans, dp[i][x]);

    print(ans);
}
