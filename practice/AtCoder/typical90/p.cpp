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
    i64 n; input >> n;
    i64 a, b, c; input >> a >> b >> c;

    i64 ans = INF64;

    FOR(i, 10000) {
        FOR(j, 10000 - i) {
            i64 v = (n - (a * i + b * j));
            if(v < 0) continue;
            if(v % c) continue;
            chmin(ans, i + j + v / c);
        }
    }

    print(ans);
}
