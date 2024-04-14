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
    i64 n, k; input >> n >> k;
    vector<i64> a(n); input >> a;
    auto u = lib::sorted(a).unique();

    lib::counter cnt(a);
    i64 mx = 0;
    ITR(v, c, cnt) chmax(mx, c);
    auto x = a | std::views::filter([&](i64 v) { return cnt[v] == mx; });
    vector<i64> b(ALL(x));
    b.sort().unique();

    debug(u, mx, b);

    i64 ans = k * n + k * (n - u.ssize() - 1) + b[0] - b[-1];
    debug(ans);

    i64 m = 0;
    REP(i, 1, b.size()) chmax(m, b[i] - b[i - 1]);
    debug(m);

    chmax(ans, k * n + k * (n - u.ssize() - 2) + m);

    print(ans);
}
