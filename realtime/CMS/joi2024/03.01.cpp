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
    int n; input >> n;
    i64 l; input >> l;
    vector<i64> p(n); input >> p;
    p.sort();

    p.push_back(0);
    p.push_back(0);

    int q = 0; input >> q;
    REP(q) {
        i64 s, g, t; input >> s >> g >> t;

        p[n] = s;
        p[n+1] = g;

        lib::valgrid<i64> dp(1 << (n + 2), n + 2, INF32);
        dp[1 << n][n] = 0;

        REP(x, 1 << (n + 2)) {
            REP(i, n + 2) REP(j, n + 2) {
                chmin(dp[x | (1 << i)][i], dp[x][j] + std::abs(p[i] - p[j]) * std::popcount((unsigned)x));
            }
        }

        i64 x = dp[(1 << (n + 2)) - 1][n + 1];
        debug(x);
        print.yesno(x + n <= t);
    }
}
