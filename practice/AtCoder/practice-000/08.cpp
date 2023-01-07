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

#include <atcoder/dsu>
#include "graph.hpp"

signed main() {
    int n; cin >> n;
    lib::graph G(n);

    REP(i, n) {
        int u, v; cin >> u >> v; --u, --v;
        G.add_edge_bidirectionally(u, v);
    }

    unordered_set<int> cycle;

    {
        vector<int> prev(n, -1);
        auto dfs = [&](auto &dfs, int v) -> bool {
            for(auto& nv : G[v]) {
                if(nv.to == prev[v]) continue;
                debug(v, nv.to);
                if(prev[nv.to] != -1) {
                    cycle.insert(nv.to);
                    auto p = v;
                    debug(p, nv.to);
                    while(p != nv.to) {
                        cycle.insert(p);
                        p = prev[p];
                    }
                    return true;
                }
                prev[nv.to] = v;
                if(dfs(dfs, nv.to)) return true;;
            }
            return false;
        };
        prev[0] = -2;
        dfs(dfs, 0);
    }
    debug(cycle);

    atcoder::dsu uf(n);

    {
        queue<int> que;
        vector<int> prev(n, -1);

        que.push(0), prev[0] = 0;

        while(!que.empty()) {
            auto v = que.front(); que.pop();
            for(auto& nv : G[v]) {
                if(not cycle.count(v)) {
                    uf.merge(v, nv.to);
                }
                if(prev[nv.to] >= 0) continue;
                prev[nv.to] = v;
                que.push(nv.to);
            }
        }
    }
    debug(uf.groups());

    int q; cin >> q;
    REP(q) {
        int x, y; cin >> x >> y; --x, --y;
        print((uf.same(x, y) ? "Yes" : "No"));
    }

    return 0;
}
