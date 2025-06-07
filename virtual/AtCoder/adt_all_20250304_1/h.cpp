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

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n >> m;
    vector<i64> l(m), d(m), k(m), c(m), a(m), b(m);
    input >> uni::views::zip(l, d, k, c, a, b);
    a -= 1, b -= 1;

    uni::graph<i64> g(n);

    ITR(u, v, w, uni::views::zip(a, b, c)) {
        g.add_edge(v, u, w);
    }

    std::priority_queue<spair<i64>> pq;
    vector<i64> dist(n, -INF64);

    dist[n-1] = INF64;
    pq.emplace(INF64, n-1);

    while(!pq.empty()) {
        auto [ t, v ] = pq.top(); pq.pop();
        if(dist[v] > t) continue;

        ITR(e, g[v]) {
            debug(v, e, e.index);
            i64 pd = uni::min(uni::div_floor((t - c[e.index] - l[e.index]), d[e.index]), k[e.index] - 1) * d[e.index] + l[e.index];
            if(dist[e] > pd) continue;
            dist[e] = pd;
            pq.emplace(pd, e);

            debug(dist);
        }
    }

    ITR(x, dist | std::views::take(n - 1)) {
        if(x < 0) print("Unreachable");
        else print(x);
    }
}
