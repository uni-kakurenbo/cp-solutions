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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int a, b;
    u64 c;
    input >> a >> b >> c;

    lib::multi_container<i64, 3> dp(61, 61, 61, -1);
    dp[0][0][0] = 0;

    REP(i, 60) {
        REP(p, 60) REP(q, 60) {
            if(dp[i][p][q] < 0) continue;
            // debug(i, p, q, dp[i][p][q], dp[i][p][q] | (1UL << i));
            assert(std::popcount((u64)dp[i][p][q]) == p);
            dp[i + 1][p][q + lib::bit(c, i)] = dp[i][p][q];
            dp[i + 1][p + 1][q + lib::bit(~c, i)] = dp[i][p][q] | (1UL << i);
        }
        // debug(dp);
    }

    u64 x = dp[60][a][b];

    if(x == -1UL) {
        print(-1);
        return;
    }

    u64 y = x ^ c;
    assert(x < (1UL << 60));
    assert(y < (1UL << 60));
    assert(std::popcount(x) == a);
    assert(std::popcount(y) == b);
    print(x, y);
}
