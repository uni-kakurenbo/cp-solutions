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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}


#include "numeric/boundary_seeker.hpp"

void solve() {
    i64 k; input >> k;

    auto count = [&](i64 t) {
        lib::multi_container<i64, 3> dp(15, 2, 11);

        REP(i, 14) {
            if(t / lib::pow(10L, i) == 0) dp[i][0][0] = 1;
            else dp[i][1][0] = 1;
        }

        REPD(d, 0, 14) {
            int n = t / lib::pow(10L, d) % 10;
            // debug(d, n);
            REP(i, 10) {
                if(n != i) dp[d][0][n] += dp[d + 1][0][i];
                REP(j, 10) {
                    if(i == j) continue;
                    dp[d][1][j] += dp[d + 1][1][i];
                    if(j < n) dp[d][1][j] += dp[d + 1][0][i];
                }
            }
            // debug(dp[d][0], dp[d][1]);
        }
        return dp[0][0].sum() + dp[0][1].sum();
    };

    auto ok = [&](i64 v) -> bool {
        // debug(v);
        return count(v) <= k;
    };

    lib::boundary_seeker<i64> seeker(ok);
    print(seeker.bound(0, INF64) + 1);
}
