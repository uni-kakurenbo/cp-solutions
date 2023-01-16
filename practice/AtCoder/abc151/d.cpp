/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "utility/applier.hpp"

#include "grid.hpp"
#include "graph.hpp"
#include "graph/bfs.hpp"
#include "graph/from_grid.hpp"

signed main() {
    int h, w; cin >> h >> w;

    lib::unfolded_grid<char> grid(h, w); grid.read();
    lib::graph<> graph;
    graph.from_grid(grid);

    debug(grid, graph);

    lib::maximum<int> ans = -1;

    REP(si, h) REP(sj, w) {
        if(grid(si, sj) == '#') continue;
        vector<ll> dists;
        graph.bfs(grid.id(si,sj), &dists);
        REP(gi, h) REP(gj, w) {
            if(grid(gi, gj) == '#') continue;
            ans <<= dists[grid.id(gi,gj)];
        }
    }

    print(ans);

    return 0;
}
