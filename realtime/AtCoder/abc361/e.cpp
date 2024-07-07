/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

#include "graph/tree_diamiter.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    uni::graph<i64> g(n); g.read_bidirectionally<true>(n - 1);

    i64 ans = 0;
    REP(i, n - 1) ans += g.edges()[i].cost;
    ans *= 2;

    ans -= uni::tree_diamiter(g).first;
    print(ans);
}
