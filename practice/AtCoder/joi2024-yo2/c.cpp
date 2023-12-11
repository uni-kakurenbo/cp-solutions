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
#include "graph/shortest_path.hpp"

void solve() {
    int n; input >> n;
    valarray<int> s(n);
    REP(i, n) {
        char c; input >> c;
        if(c == 'R') s[i] = 1;
        if(c == 'G') s[i] = 2;
        if(c == 'B') s[i] = 3;
    }
    i64 a, b, c; input >> a >> b >> c;

    lib::leveler leveler(n, 5);

    lib::graph<i64> G(leveler.sup() + 2);

    REP(i, n-1) FOR(v, 1, 3) {
        int nv = lib::mod(v, 3) + 1;
        i64 cost = c * (nv != s[i+1]);
        debug(v, nv, s[i+1], cost);
        G.add_edge(leveler.convert(i, v), leveler.convert(i+1, nv), cost);
    }

    REP(i, n-1) {
        G.add_edge(leveler.convert(i, 0), leveler.convert(i+1, 0), b);
        G.add_edge(leveler.convert(i, 4), leveler.convert(i+1, 4), a);
    }

    REP(i, n) {
        G.add_edge(leveler.convert(i, 3), leveler.convert(i, 0), 0);
        G.add_edge(leveler.convert(i, 4), leveler.convert(i, 3), 0);
    }

    G.add_edge(leveler.sup(), leveler.convert(0, 0), b);
    G.add_edge(leveler.sup(), leveler.convert(0, 4), a);
    G.add_edge(leveler.sup(), leveler.convert(0, 1), c * (s[0] != 1));
    G.add_edge(leveler.convert(n-1, 0), leveler.sup() + 1, 0);

    auto dists = G.distances_with_cost(leveler.sup());

    print(dists[leveler.sup() + 1]);
}
