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
    int x, y, r, n; input >> x >> y >> r >> n;

    lib::grid<char,string> G(n*2+1, n*2+1, '.');

    FOR(i, -n, n) FOR(j, -n, n) {
        if((i - x) * (i - x) + (j - y) * (j - y) <= r * r) {
            G[i+n][j+n] = '#';
        }
    }

    ITR(v, G) print(lib::join(v, " "));
}
