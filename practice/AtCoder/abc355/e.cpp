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

using mint = uni::static_modint_32bit<100>;

auto query(u32 l, u32 r) {
    i32 sign = 1;
    if(l > r) std::swap(l, r), sign *= -1;

    u32 i = std::countr_zero(r - l);
    u32 j = l / (r - l);

    print("?", i, j).flush();
    mint sum; input >> sum;
    return sum * sign;
}

#include "graph/shortest_path.hpp"

void solve() {
    i32 n, l, r; input >> n >> l >> r; ++r;
    u32 m = uni::shiftl(1U, n);

    uni::graph<i32> graph(m + 1);
    FOR(d, n) {
        u32 p = uni::shiftl(1U, d);
        REP(i, 0, m, p) {
            graph.add_edge_bidirectionally(i, i + p);
        }
    }

    uni::vector<i32> dists, prev;
    graph.shortest_path_without_cost(l, &dists, &prev);

    auto path = uni::restore_path(r, prev);
    debug(path);

    mint ans = 0;

    ITR(s, path | uni::views::slide(2)) {
        debug(s);
        ans += query(s[0], s[1]);
    }

    print("!", ans);
}
