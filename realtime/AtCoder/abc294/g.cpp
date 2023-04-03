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

#include "data_structure/fenwick_tree.hpp"
#include "data_structure/range_action/range_sum.hpp"
#include "graph/lowest_common_ancestor.hpp"

signed main() {
    i64 n; cin >> n;

    struct edge { i64 id, to, cost; edge(i64 id, i64 to, i64 cost) : id(id), to(to), cost(cost) {}};
    std::vector<std::vector<edge>> G(n);

    std::vector<edge> E;
    std::map<std::pair<i64,i64>,i64> vtoe;
    std::map<std::pair<i64,i64>,std::pair<i64,i64>> etoi;
    std::vector<int> S(n);

    REP(i, n-1) {
        i64 u, v, w; cin >> u >> v >> w; --u, --v;
        E.emplace_back(u, v, w);
        G[u].emplace_back(i+1, v, w);
        G[v].emplace_back(i+1, u, w);
        vtoe[{ u, v }] = vtoe[{ v, u }] = i;
    }

    lib::fenwick_tree<lib::actions::range_sum<i64>> cost(2*n);
    std::vector<i64> tour;

    auto dfs = [&](auto& dfs, int v, int p) mutable -> void {
        if(p >= 0) cost.add(tour.size(), E[vtoe[{ p, v }]].cost);
        S[v] = tour.size();
        etoi[{ v, p }].first = etoi[{ p, v }].first = tour.size();
        tour.push_back(v);

        ITR(e, G[v]) {
            if(e.to == p) continue;
            dfs(dfs, e.to, v);
        }

        if(p >= 0) cost.add(tour.size(), -E[vtoe[{ p, v }]].cost);
        etoi[{ v, p }].second = etoi[{ p, v }].second = tour.size();
        tour.push_back(-v);
    };
    dfs(dfs, 0, -1);

    lib::lowest_common_ancestor LCA(G);

    int q; cin >> q;
    REP(q) {
        int c; cin >> c;
        debug(c);
        if(c == 1) {
            int i, w; cin >> i >> w; --i;
            debug(E[i].id, E[i].to);
            auto id = etoi[{E[i].id, E[i].to}];
            debug(id);
            cost.set(id.first, w);
            cost.set(id.second, -w);
        }
        if(c == 2) {
            int u, v; cin >> u >> v; --u, --v;
            debug(S[u], S[v], LCA(u, v));
            print(cost.prod(S[u]+1) + cost.prod(S[v]+1) - 2 * cost.prod(S[LCA(u, v)]+1));
        }

        debug(tour);
        debug(cost);
    }

    return 0;
}
