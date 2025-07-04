/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/small.hpp"

#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long;

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 0;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
        solve();
    // }
    return 0;
}

#include "snippet/aliases.hpp"



// #include "template/debug.hpp"
// #include "template/warnings.hpp"
void solve() {
    i32 n; std::cin >> n;
    std::vector<i64> xs(n), ys(n);

    for(auto i : std::views::iota(0, n)) {
        std::cin >> xs[i] >> ys[i];
    }

    using P = std::pair<i32, i32>;
    std::vector<std::vector<P>> graph(n);

    REP(2) {
        std::vector<i32> inds(n); std::iota(ALL(inds), 0);
        std::ranges::sort(inds, [&](auto i, auto j) { return xs[i] < xs[j]; });

        REP(i, 1, n) {
            auto u = inds[i - 1], v = inds[i];
            auto d = std::min(std::abs(xs[u] - xs[v]), std::abs(ys[u] - ys[v]));

            graph[u].emplace_back(v, d);
            graph[v].emplace_back(u, d);
        }

        REP(i, n) std::swap(xs[i], ys[i]);
    }

    std::priority_queue<P, std::vector<P>, std::greater<>> pq;
    std::vector<i64> dist(n, 1L << 60);

    pq.emplace(dist[0] = 0, 0);

    while(!pq.empty()) {
        auto [ d, v ] = pq.top(); pq.pop();

        if(dist[v] < d) continue;

        for(auto [ nv, cost ] : graph[v]) {
            auto nd = d + cost;
            if(dist[nv] <= nd) continue;
            pq.emplace(dist[nv] = nd, nv);
        }
    }

    std::cout << dist[n - 1] << "\n";
}
