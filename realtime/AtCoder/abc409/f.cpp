/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "graph/manhattan_minimum_spanning_tree.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n, q; input >> n >> q;
    // using point = uni::point<i64>;
    vector<i64> xs(n), ys(n); input >> uni::views::zip(xs, ys);
    uni::graph<i64> g(n + q);

    ITR(u, v, w, uni::manhattan_mst_candidate_edges(ALL(xs), ALL(ys))) {
        g.add_edge_bidirectionally(u, v, w);
    }

    uni::disjoint_set ds(n + q);

    REP(i, q) {
        i32 t = 0; input >> t;
        if(t == 1) {
            i32 a, b; input >> a >> b;

            i64 mdist = INF64;
            REP(v, n) {
                auto dist = uni::manhattan_distance<i64>({ xs[v], ys[v] }, { a, b });
                chmin(mdist, dist);
            }

            REP(v, n) {
                auto dist = uni::manhattan_distance<i64>({ xs[v], ys[v] }, { a, b });
                if(mdist == dist) {
                    g.add_edge_bidirectionally(v, n, dist);
                }
            }

            xs.push_back(a), ys.push_back(b);
            ++n;
        }
        if(t == 2) {
            i64 mdist = INF64;

            REP(v, n) {
                ITR(e, g[v]) {
                    if(ds.same(v, e.to)) continue;
                    chmin(mdist, e.cost);
                }
            }

            debug(mdist);

            if(mdist == INF64) {
                print(-1);
                continue;
            }

            REP(v, n) {
                ITR(e, g[v]) {
                    if(ds.same(v, e.to)) continue;
                    if(mdist == e.cost) {
                        ds.merge(v, e.to);
                        debug(v, e.to);
                    }
                }
            }

            print(mdist);
        }
        if(t == 3) {
            i32 u, v; input >> u >> v; --u, --v;
            print.yesno(ds.same(u, v));
        }
    }
}
