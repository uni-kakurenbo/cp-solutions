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

#include "numeric/leveler.hpp"

void solve() {
    int m, r; input >> m >> r;

    lib::leveler<int> lv(m, 10);
    lib::graph<int> G(lv.sup());

    REP(d, m) REP(i, 10) {
        G.add_edge(lv.convert(d, i), lv.convert(lib::mod(d * 10 + i, m), i));

        vector<int> nxt;
        if(i == 0) nxt.push_back(1);
        if(i == 1) nxt.push_back(0), nxt.push_back(2), nxt.push_back(4);
        if(i == 2) nxt.push_back(1), nxt.push_back(3), nxt.push_back(5);
        if(i == 3) nxt.push_back(2), nxt.push_back(6);
        if(i == 4) nxt.push_back(1), nxt.push_back(5), nxt.push_back(7);
        if(i == 5) nxt.push_back(2), nxt.push_back(4), nxt.push_back(6), nxt.push_back(8);
        if(i == 6) nxt.push_back(3), nxt.push_back(5), nxt.push_back(9);
        if(i == 7) nxt.push_back(4), nxt.push_back(8);
        if(i == 8) nxt.push_back(5), nxt.push_back(7), nxt.push_back(9);
        if(i == 9) nxt.push_back(6), nxt.push_back(8);
        ITR(j, nxt) {
            G.add_edge(lv.convert(d, i), lv.convert(d, j));
        }
    }

    const auto dists = G.distances_without_cost(lv.convert(0, 0));
    // debug(dists);

    int ans = INF32;
    REP(i, 10) {
        chmin(ans, dists[lv.convert(r, i)]);
    }

    print(ans);
}
