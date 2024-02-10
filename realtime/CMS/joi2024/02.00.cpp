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

#include "graph/shortest_path.hpp"

void solve() {
    i64 n, m; input >> n >> m;
    i64 s, t, l, k; input >> s >> t >> l >> k; --s, --t;
    lib::graph<i64> G(n); G.read_bidirectionally<true>(m);

    auto dists_s = G.distances_with_cost(s);
    auto dists_t = G.distances_with_cost(t);

    if(dists_s[t] <= k) {
        print(lib::nCr(n, 2L));
        return;
    }

    auto dists_t_sorted = lib::sorted(dists_t);
    debug(dists_s, dists_t, dists_t_sorted);

    i64 ans = 0;

    ITR(v, dists_s) {
        auto itr = dists_t_sorted.upper_bound(k - l - v);
        debug(k - l - v, itr);
        ans += itr - dists_t_sorted.begin();
    }
    debug(ans);

    REP(i, n) {
        ans -= (dists_s[i] + dists_t[i] <= k - l);
    }

    print(ans);
}
