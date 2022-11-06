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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "grid.hpp"
#include "graph.hpp"
#include "graph/bfs.hpp"
#include "graph/from_grid.hpp"

signed main() {
    int h, w; cin >> h >> w;
    Grid<char,string> C(h, w); C.read();

    int si, sj; si = sj = -1;
    REP(i, h) REP(j, w) if(C(i,j) == 'S') si = i, sj = j;

    Graph<> G;
    G.from_grid(C);

    ITRM(di, dj, DIRS4) {
        int ni = si + di, nj = sj+ dj;
        if(ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
        if(C(ni, nj) == '#') continue;

        vector<int> dists;
        G.bfs(ni*w+nj, &dists);

        ITRM(di, dj, DIRS4) {
            int mi = si + di, mj = sj+ dj;
            if(ni == nj and nj == mj) continue;
            if(mi < 0 or mi >= h or mj < 0 or mj >= w) continue;
            if(C(mi, mj) == '#') continue;
            if(dists[mi*w + mj] > 0) {
                print("Yes");
                exit(0);
            }
        }
    }

    print("No");

    return 0;
}
