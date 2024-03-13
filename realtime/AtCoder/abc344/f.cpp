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
    int n; input >> n;
    lib::unfolded_grid<i64> p(n, n), r(n, n-1), d(n-1, n);
    input >> p >> r >> d;

    lib::compressed<i64> rank(p);
    debug(p, r, d);
    debug(rank);

    lib::multi_container<spair<i64>, 3, std::vector> dp(n, n, rank.rank_sup(), spair<i64>{ INF64, 0 });
    dp(0, 0, 0) = { 0, 0 };

    REP(i, n) REP(j, n) {
        REP(k, rank.rank_sup()) {
            i64 max_k = lib::max(rank.value(k), p(i, j));
            i64 ind = rank.rank(max_k);
            debug(k, rank.value(k), max_k, ind);
            // assert(ind < rank.rank_sup());
            if(i < n - 1) {
                i64 stay = lib::div_ceil(d(i, j) + dp(i, j, k).second, max_k);
                i64 money = -dp(i, j, k).second + stay * max_k - d(i, j);
                debug(stay, money, i, j, k, dp(i, j, k).first + stay + 1, -money);
                chmin(dp(i + 1, j, ind), spair<i64>{ dp(i, j, k).first + stay + 1, -money });
            }
            if(j < n - 1) {
                i64 stay = lib::div_ceil(r(i, j) + dp(i, j, k).second, max_k);
                i64 money = -dp(i, j, k).second + stay * max_k - r(i, j);
                debug(stay, money, i, j, k, dp(i, j, k).first + stay + 1, -money);
                chmin(dp(i, j + 1, ind), spair<i64>{ dp(i, j, k).first + stay + 1, -money });
            }
        }
    }
    debug(dp);

    print(std::ranges::min(dp[n - 1][n - 1]).first);
}
