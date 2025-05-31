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

#include <atcoder/scc>

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n >> m;
    vector<i64> a(n); input >> a;

    uni::graph<i32> g(n); g.read_bidirectionally(m);
    atcoder::scc_graph h(n);
    uni::graph<i32> k(n);

    REP(i, n) {
        for(auto& e : g[i]) {
            auto x = a[e.from], y = a[e.to];
            if(x <= y) {
                h.add_edge(e.from, e.to);
                k.add_edge(e.from, e.to);
            }
        }
    }

    auto vs = h.scc();
    debug(vs);

    vector<i64> dist(n, -INF64);

    for(auto& v : vs) {
        std::ranges::sort(v);

        if(std::ranges::binary_search(v, 0)) {
            for(auto x : v) dist[x] = 1;
        }

        auto nv = -INF64;

        for(auto& x : v) {
            chmax(nv, dist[x]);
        }

        for(auto& x : v) {
            dist[x] = nv;
        }

        debug(nv);

        for(auto& x : v) {
            for(auto& e : k[x]) {
                if(std::ranges::binary_search(v, e.to)) continue;
                chmax(dist[e], nv + 1);
            }
        }
        debug(dist);
    }

    print(uni::max(0, dist[n - 1]));
}
