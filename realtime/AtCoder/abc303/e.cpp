/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "graph.hpp"
#include "iterable/inverse.hpp"

void solve() {
    int n; cin >> n;
    std::map<int,vector<lib::internal::graph_impl::edge<int,int>>> G;

    valarray<int> deg(n);

    REP(i, n-1) {
        int u, v; cin >> u >> v; --u, --v;
        G[u].emplace_back(u, v, 1), G[v].emplace_back(v, u, 1);
        deg[u]++, deg[v]++;
    }
    auto deg2 = deg;

    set<int> cands;
    REP(i, n) if(deg[i] == 1) cands.insert(i);
    debug(deg, cands);

    vector<int> centers;
    set<int> removed;

    while(not cands.empty()) {
        debug(cands);
        set<int> nxt;
        ITR(v, cands) {
            if(removed.contains(v)) continue;
            ITR(e, G[v]) {
                if(removed.contains(e.to)) continue;
                int c = e.opposite(v);
                centers.push_back(c);
                deg[c] = 0;
                nxt.remove(c);
                removed.insert(c);
                ITR(f, G[c]) {
                    if(removed.contains(f.to)) continue;
                    int u = f.opposite(c);
                    deg[u] = 0;
                    nxt.remove(u);
                    removed.insert(u);
                    ITR(g, G[u]) {
                        if(removed.contains(g.to)) continue;
                        int w = g.opposite(u);
                        --deg[w];
                        if(deg[w] == 1) nxt.insert(w);
                    }
                }
            }
        }
        cands = nxt;
    }

    debug(centers);

    std::sort(ALL(centers), [&](int p, int q) {
        if(deg2[p] != deg2[q]) return deg2[p] < deg2[q];
        return p < q;
    });
    centers.erase(std::unique(ALL(centers)), centers.end());
    debug(centers);

    ITR(i, centers) {
        print << deg2[i] << " ";
    }
    print();
}
