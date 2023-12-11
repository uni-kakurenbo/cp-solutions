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
    i64 n, s; input >> n >> s;
    valarray<i64> a(n); input >> a;

    lib::accumulation<i64> cum(a);
    debug(cum);

    valarray<i64> r(n);
    REP(i, n) {
        auto itr = std::upper_bound(cum.begin() + i, cum.end(), cum[i] + s) - 1;
        r[i] = itr - cum.begin();
    }
    debug(cum);
    debug(r);

    valarray<i64> dp(n + 1);
    dp[n] = 0;
    REPD(i, n) dp[i] = (r[i] - i) + (dp[r[i]] + n - r[i]);
    print(dp.sum());
}
