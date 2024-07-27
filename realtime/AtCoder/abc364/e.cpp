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
    i64 n, x, y; input >> n >> x >> y;
    vector<i64> a(n), b(n); input >> uni::views::zip(a, b);

    i64 ans = 0;

    REP(2) {
        uni::multi_container<i64, 3> dp(n + 1, n + 1, x + 1, INF64);
        dp[0][0][0] = 0;

        uni::vector<i32> ids(n); std::iota(ALL(ids), 0);
        ids.sort([&](auto i, auto j) { return a[i] < a[j]; });

        a = uni::ordered_by(a, ids);
        b = uni::ordered_by(b, ids);
        debug(a, b);

        REP(i, n) {
            REP(k, n) {
                REP(j, x) {
                    chmin(dp[i + 1][k][j], dp[i][k][j]);
                    if(j + a[i] <= x) chmin(dp[i + 1][k + 1][j + a[i]], dp[i][k][j] + b[i]);
                }
            }
        }
        // debug(dp);

        FOR(i, n) FOR(k, n) FOR(j, x) if(dp[i][k][j] <= y) chmax(ans, k);

        std::swap(a, b);
        std::swap(x, y);
    }

    print(std::min(ans + 1, n));
}
