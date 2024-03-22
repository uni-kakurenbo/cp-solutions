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
    i64 n, c; input >> n >> c;
    valarray<i64> a(n); input >> a;
    auto b = a;
    b *= (c - 1);

    lib::accumulation cum(b);

    i64 s;
    i64 ans = s = a.sum();

    auto max_r = cum;
    FORD(i, 1, n) chmax(max_r[i - 1], max_r[i]);
    debug(s, b, cum, max_r);

    REP(l, n) {
        chmax(ans, s + max_r[l + 1] - cum[l]);
    }

    print(ans);
}
