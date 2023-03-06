/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"
#include "graph/bfs.hpp"

#include "numeric/prime.hpp"

signed main() {
    int n, m; std::cin >> n >> m;
    std::vector<int> w(n); input >> w;
    lib::graph G(n); G.read_bidirectionally(m);

    std::set<int> p;
    REP(i, n) {
        if(lib::is_prime(w[i])) p.insert(i);
    }

    int max = -1;
    bool f = 1;
    REP(i, n) {
        auto dists = G.bfs(i);
        int cnt = 0;
        f &= p.count(i);
        REP(j, n) {
            cnt += dists[j] >= 0 and p.count(j);
        }
        debug(cnt);

        chmax(max, cnt);
    }
    debug(max);

    REP(i, n+1) print(!(i==0 and f) and i <= max ? "Yes" : "No");

    return 0;
}
