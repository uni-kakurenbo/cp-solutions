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

#include "numeric/subset_enumerator.hpp"

using point = uni::point<i64>;

void solve() {
    u32 n, k; input >> n >> k;
    vector<point> ps(n); input >> ps;

    vector<i64> dist(1 << n, 0);
    REP(s, 1UL << n) {
        REP(i, n) {
            if(!uni::bit(s, i)) continue;
            REP(j, n) {
                if(!uni::bit(s, j)) continue;
                chmax(dist[s], uni::squared_distance(ps[i], ps[j]));
            }
        }
    }
    debug(dist);

    uni::multi_container<i64, 2> dp(k + 1, 1UL << n, INF64);
    dp[0][0] = 0;

    REP(cnt, k) {
        REP(s, 1UL << n) {
            ITR(t, uni::subset_enumerator(s)) {
                chmin(dp[cnt + 1][s], uni::max(dp[cnt][t], dist[s & (~t)]));
            }
        }
    }
    debug(dp);

    print(dp[k][-1]);
}
