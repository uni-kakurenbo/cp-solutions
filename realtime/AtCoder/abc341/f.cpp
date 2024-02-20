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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "graph/topological_sort.hpp"

void solve() {
    int n, m; input >> n >> m;
    valarray<int> u(m), v(m); input >> lib::views::zip(u, v);
    u -= 1, v -= 1;

    valarray<i64> w(n), x(n); input >> w >> x;

    lib::graph<int> graph(n);
    ITR(i, j, lib::views::zip(u, v)) {
        if(w[i] == w[j]) continue;
        if(w[j] < w[i]) std::swap(j, i);
        graph.add_edge(i, j);
    }

    vector<int> vs(n);
    graph.sort_topologically(&vs);
    // vs.reverse();
    debug(vs);

    int sup = w.max() + 1;
    lib::valgrid<i64> dp(n, sup, -INF32);
    REP(i, n) dp[i][0] = 1;

    ITR(i, vs) {
        i64 max = dp[i].max();
        ITR(j, graph[i]) {
            REPD(s, w[j] - w[i]) {
                chmax(dp[j][s + w[i]], dp[j][s] + max);
            }
        }
        debug(dp);
    }

    i64 ans = 0;
    REP(i, n) {
        ans += dp[i].max() * x[i];
    }

    print(ans);
}
