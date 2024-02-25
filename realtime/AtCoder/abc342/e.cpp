/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

void solve() {
    int n, m; input >> n >> m;

    valarray<i64> l(m), d(m), k(m), c(m), a(m), b(m);
    input >> lib::views::zip(l, d, k, c, a, b);
    a -= 1, b -= 1;

    lib::graph<i64> graph(n);
    ITR(u, v, w, lib::views::zip(a, b, c)) {
        graph.add_edge(v, u, w);
    }

    valarray<i64> ans(n, -INF64);
    std::priority_queue<spair<i64>> pq;
    REP(i, n-1, n) {
        ans[i] = INF64;
        pq.emplace(INF64, i);
    }

    while(!pq.empty()) {
        auto [ t, v ] = pq.top(); pq.pop();
        if(ans[v] > t) continue;
        ITR(nv, graph[v]) {
            debug(v, nv, nv.index);
            i64 last = lib::min(lib::div_floor((t - c[nv.index] - l[nv.index]), d[nv.index]), k[nv.index] - 1) * d[nv.index] + l[nv.index];
            if(ans[nv] > last) continue;
            ans[nv] = last;
            pq.emplace(last, nv);
        }

        debug(ans);
    }

    ITR(x, ans | std::views::take(n - 1)) {
        if(x < 0) print("Unreachable");
        else print(x);
    }
}
