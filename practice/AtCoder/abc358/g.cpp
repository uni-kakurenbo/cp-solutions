/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 h, w, k; input >> h >> w >> k;
    i32 si, sj; input >> si >> sj; --si, --sj;
    uni::grid<i64> a(h, w); input >> a;

    uni::grid<i64> dp(h, w, -INF64);
    dp[si][sj] = 0;
    i64 ans = 0;

    FOR(t, std::min(h * w, k)) {
        uni::grid<i64> next(h, w, -INF64);

        REP(i, h) REP(j, w) {
            ITR(ni, nj, a.vicinities4(i, j)) {
                chmax(next[i][j], dp[ni][nj] + a(i, j));
            }
        }

        REP(i, h) REP(j, w) {
            chmax(ans, dp(i, j) + a(i, j) * (k - t));
        }

        dp = std::move(next);
    }

    print(ans);
}
