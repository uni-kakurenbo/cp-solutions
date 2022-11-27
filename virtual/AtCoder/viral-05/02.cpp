/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "graph.hpp"
using namespace Lib;

signed main() {
    int n, m; cin >> n >> m;
    vector<int> h(n); REP(i, n) cin >> h[i];
    Graph G(n);

    LOOP(m) {
        int a, b; cin >> a >> b; --a, --b;
        G.add_edge<Graph<>::EdgeType::Undirected>(a, b);
    }

    int ans = 0;
    REP(i, n) {
        int flag = true;
        ITR(v, G[i]) flag &= h[v.to] < h[i];
        ans += flag;
    }

    print(ans);

    return 0;
}
