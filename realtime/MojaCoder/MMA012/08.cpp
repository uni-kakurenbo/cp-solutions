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
#include "graph/from_grid.hpp"

signed main() {
    int h, w; cin >> h >> w;
    Lib::Grid<char,string> grid(h, w); grid.read();
    Lib::Graph graph; graph.from_grid(grid);

    auto bfs = [&](const int s) {
        int i_min, j_min, i_max, j_max;
        queue<int> que;
        vector<int> dists(h*w, -1);

        que.push(s), dists[s] = 0;

        while(!que.empty()) {
            auto v = que.front(); que.pop();
            for(auto nv : graph[v]) {
                if(dists[nv.to] >= 0) continue;
                dists[nv.to] = dists[v] + 1;
                que.push(nv.to);
                int i = nv.to / w, j = nv.to % w;
                chmin(i_min, i), chmin(j_min, j);
                chmax(i_max, i), chmax(j_max, j);
            }
        }
        return tuple<int,int,int,int> { i_min, i_max, j_min, j_max };
    };

    REP(si, h) REP(sj, h) {
        if(grid(si, sj) == '.') continue;
        auto [i_min, i_max, j_min, j_max] = bfs(si*w + sj);
        if(i_min == )
    }

    return 0;
}
