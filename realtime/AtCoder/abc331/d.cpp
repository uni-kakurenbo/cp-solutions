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
    int n, q; input >> n >> q;
    lib::grid<char> G(n, n); input >> G;
    lib::grid<int> H(2 * n, 2 * n);

    REP(i, 2 * n) REP(j, 2 * n) {
        H(i, j) = G(i % n, j % n) == 'B';
    }

    lib::accumulation_2d<i64> cum(ALL(H));

    REP(q) {
        int a, b, c, d; input >> a >> b >> c >> d;
        ++c, ++d;

        i64 e = lib::div_ceil(a + 1, n) * n;
        i64 f = lib::div_ceil(b + 1, n) * n;
        i64 g = lib::div_floor(c, n) * n;
        i64 h = lib::div_floor(d, n) * n;

        a %= n, b %= n, c %= n, d %= n;

        i64 p = (g - e) / n;
        i64 q = (h - f) / n;

        i64 ans = 0;

        ans += cum({ a, n }, { b, n });
        ans += cum({ 0, c }, { b, n });
        ans += cum({ a, n }, { 0, d });
        ans += cum({ 0, c }, { 0, d });

        ans += cum({ 0, n }, { b, n }) * p;
        ans += cum({ 0, n }, { 0, d }) * p;

        ans += cum({ a, n }, { 0, n }) * q;
        ans += cum({ 0, c }, { 0, n }) * q;

        ans += cum({ 0, n }, { 0, n }) * p * q;

        print(ans);
    }
}
