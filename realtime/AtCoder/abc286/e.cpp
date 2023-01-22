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
/* #endregion */

#include "grid.hpp"
#include "graph.hpp"
#include "graph/dijkstra.hpp"

constexpr ull BASE = 1LL << 32;


using cost = pair<ll,ll>;

cost operator+(const cost& a, const cost& b) {
    return { a.first + b.first, a.second + b.second };
}

signed main() {
    int n; cin >> n;
    vector<ll> a(n); input >> a;

    lib::grid<char,string> s(n, n); input >> s;


    lib::grid<cost> dists(n, n, { INT32_MAX, 0 });
    REP(i, n) dists[i][i] = { 0, 0 };
    REP(i, n) REP(j, n) {
        if(s[i][j] == 'Y') dists[i][j] = { 1, -a[j] };
    }
    REP(k, n) REP(i, n) REP(j, n) {
        chmin(dists[i][j],  dists[i][k] + dists[k][j]);
    }
    debug(dists);

    int q; cin >> q;
    REP(q) {
        int u, v; cin >> u >> v; --u, --v;
        auto [edges, cost] = dists[u][v];
        if(edges >= INT32_MAX) print("Impossible");
        else print(edges, a[u] - cost);
    }

    return 0;
}
