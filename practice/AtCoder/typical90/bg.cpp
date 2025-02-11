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

#include "template/warnings.hpp"
#include "graph/reachability_test.hpp"

void solve() {
    i32 n, m, q; input >> n >> m >> q;
    uni::graph<i32> graph(n); graph.read(m);
    valarray<spair<i32>> qs(q); input >> qs;
    ITRR(a, b, qs) --a, --b;

    auto res = graph.test_reachability(qs);
    ITR(v, res) print.yesno(v);
}
