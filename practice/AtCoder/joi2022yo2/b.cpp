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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

#include "grid.hpp"
#include "graph.hpp"
#include "graph/bfs.hpp"

signed main() {
    int h, w; cin >> h >> w;
    Lib::Grid<char,string> S(h, w);
    S.read();

    Lib::Graph<> G(h*w);

    REP(i, h) REP(j, w) {
        if(i+1 < h and S(i,j) != S(i+1,j)) {
            G.add_edge<Lib::Graph<>::EdgeType::Undirected>(i*w+j, (i+1)*w+j);
        }
        if(j+1 < w and S(i,j) != S(i,j+1)) {
            G.add_edge<Lib::Graph<>::EdgeType::Undirected>(i*w+j, i*w+(j+1));
        }
    }

    vector<int> dists;
    G.bfs(0, &dists);

    print(dists[h*w-1]);

    return 0;
}
