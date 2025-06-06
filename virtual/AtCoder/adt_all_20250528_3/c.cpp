/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "template/warnings.hpp"
void solve() {
    i64 n, s, m, l; input >> n >> s >> m >> l;
    chmin(l, s * 2);

    i64 ans = INF64;

    FOR(i, n) FOR(j, n) FOR(k, n) {
        if(6 * i + 8 * j + 12 * k >= n) {
            chmin(ans, i * s + j * m + k * l);
        }
    }

    print(ans);
}
