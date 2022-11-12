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

#include "iterable/compression.hpp"

#include "graph.hpp"
#include "graph/bfs.hpp"

signed main() {
    int n; cin >> n;

    map<int,vector<int>> G;
    LOOP(n) {
        int a, b; cin >> a >> b; --a, --b;
        G[a].push_back(b), G[b].push_back(a);
    }

    queue<int> que;
    map<int,int> dists;

    que.push(0), dists[0] = 0;

    while(!que.empty()) {
        int v = que.front(); que.pop();
        for(int nv : G[v]) {
            if(dists.count(nv)) continue;
            dists[nv] = dists[v] + 1;
            que.push(nv);
        }
    }

    debug(dists);
    print(max_element(ALL(dists))->$F+1);

    return 0;
}
