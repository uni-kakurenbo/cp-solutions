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
    uni::graph<u64> g(n); g.read_bidirectionally<true>(m);

    u64 ans = (1UL << 31) - 1;

    REPD(bit, 31) {
        uni::graph<i64> h(n);
        ITR(e, g.edges()) {
            bool use = true;
            REP(i, 31) {
                if(!uni::bit(ans, i) && uni::bit<u64>(e.cost, i)) {
                    use = false;
                }
            }

            if(!use) continue;

            if(!uni::bit(e.cost, bit)) {
                debug(e);
                h.add_edge_bidirectionally(e.from, e.to);
            }
        }

        auto dist = h.shortest_path_without_cost(0);

        if(dist[n - 1] < INF32) {
            ans ^= (1UL << bit);
        }

        debug(bit, dist[n - 1], ans);
    }

    print(ans);
}
