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
    i64 n, m; input >> n >> m;
    vector<i64> b(n), w(m); input >> b >> w;

    ITRR(x, w) chmax(x, 0);

    b.sort().reverse();
    w.sort().reverse();

    debug(b, w);
    uni::accumulation<i64> cumb(b), cumw(w);
    debug(cumb, cumw);

    i64 ans = 0;

    FOR(i, n) {
        chmax(ans, cumb[i] + (i <= m ? cumw[i] : cumw[m]));
    }

    print(ans);
}
