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

#include "grid.hpp"
#include "graph.hpp"
#include "graph/dijkstra.hpp"

signed main() {
    int h, w, n; cin >> h >> w >> n;
    int si, sj, gi, gj; cin >> si >> sj >> gi >> gj;
    --si, --sj, --gi, --gj;

    lib::grid<char,string> grid(h, w); input >> grid;
    debug(grid);
    lib::graph G(h*w);

    REP(i, h) REP(j, w) {
        ITR(di, dj, DIRS4) {
            int ni = i + di, nj = j + dj;
            if(ni < 0 or nj < 0 or ni >= h or nj >= w) continue;
            G.add_edge(i*w+j, ni*w+nj, grid[ni][nj] == '#');
        }
    }

    print(G.dijkstra(si*w+sj)[gi*w+gj]);

    REP(i, n) {

    }

    return 0;
}
