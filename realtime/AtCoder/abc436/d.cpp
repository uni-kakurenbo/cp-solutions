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

#include "graph/parse_grid.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 h, w; input >> h >> w;
    uni::grid<char, string> s(h, w); input >> s;

    uni::graph<i32> g(h * w + 26);
    g.parse_grid<true>(s, '#');

    REP(i, h) REP(j, w) {
        if('a' <= s(i, j) && s(i, j) <= 'z') {
            g.add_edge(s.id(i, j), h * w + (s(i, j) - 'a'), 1);
            g.add_edge(h * w + (s(i, j) - 'a'), s.id(i, j), 0);
        }
    }

    auto dist = g.shortest_path_with_01cost(0);
    debug(dist);

    print(uni::to_optional_if_or_over(dist[h * w - 1], INF32).value_or(-1));
}
