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


#include "graph/shortest_path.hpp"


#pragma GCC diagnostic warning "-Wshadow=local"
void solve() {

    i32 n; input >> n;
    uni::grid<char> grid(n, n); input >> grid;
    debug(grid);

    i32 ans = 0;

    REP(t, 2) {
        uni::graph<i32> graph(n * n);

        REP(i, n) REP(j, n) {
            i32 v = grid.id(i, j);
            ITR(ni, nj, grid.vicinities4(i, j)) {
                graph.add_edge(v, grid.id(ni, nj), grid(ni, nj) != (t == 0 ? 'R' : 'B'));
            }
        }

        // debug(graph);

        i32 s = (t == 0) ? 0 : grid.id(n - 1, 0);
        i32 g = (t == 0) ? grid.id(n - 1, n - 1) : grid.id(0, n - 1);

        auto d = graph.shortest_path_with_cost(s);

        debug(s, g, d, d[g]);

        ans += d[g];
    }

    print(ans);
}
