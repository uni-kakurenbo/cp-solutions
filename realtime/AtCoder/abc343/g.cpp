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

bool is_substring(string s, string t) {
    int p = 0;
    ITR(c, s) {
        auto itr = std::ranges::find(t.begin() + p, t.end(), c);
        if(itr == t.end()) return false;
        p = itr - t.begin();
    }
    return true;
}

#include "graph/minimum_paph_cover.hpp"

void solve() {
    int n; input >> n;
    vector<string> s(n); input >> s;

    lib::graph<int> graph(n);
    REP(i, n) REP(j, n) {
        debug(i, j, is_substring(s[i], s[j]));
        graph.add_edge(i, j);
    }

    print(graph.minimum_paph_cover_size_as_dag());
}
