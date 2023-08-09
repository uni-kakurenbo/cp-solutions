/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
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
    string s; cin >> s;
    string ATCODER = "atcoder";

    using edge = typename lib::virtual_graph<string,int>::edge;
    auto next = [](string s) -> vector<edge> {
        vector<edge> res;
        REP(i, 1, s.size()) {
            s.swap(i-1, i);
            res.emplace_back("", s);
            s.swap(i-1, i);
        }
        return res;
    };

    lib::virtual_graph<string,int> G(0, next);
    debug(G[ATCODER]);

    auto dists = G.distances_without_cost(ATCODER);

    // static_assert(std::is_base_of_v<std::unordered_map<string,int>, decltype(dists)>);

    print(dists[s]);
}
