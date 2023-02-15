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

#include "graph.hpp"
#include "graph/connected_components.hpp"

signed main() {
    int n; cin >> n;
    vector<ll> X(n), E(n);
    REP(i, n) input >> X[i] >> E[i];
    debug(X, E);

    // REP(i, n) {
    //     debug(X[i] - E[i], X[i] + E[i]);
    // }

    vector<int> XmE(n), XpE(n);
    iota(ALL(XmE), 0), iota(ALL(XpE), 0);

    auto compXmE = [&](int i, int j) { return X[i] - E[i] < X[j] - E[j]; };
    auto compXpE = [&](int i, int j) { return X[i] + E[i] < X[j] + E[j]; };

    sort(ALL(XmE), compXmE);
    sort(ALL(XpE), compXpE);

    debug(XmE, XpE);

    lib::graph G(n);

    REP(i, n) {
        auto a = lower_bound(ALL(XmE), i, compXmE);
        auto b = upper_bound(ALL(XpE), i, compXpE);

        bitset<16> s, t;
        REPD(i, a, XmE.end()) s.set(*i);
        REP(i, XpE.begin(), b) t.set(*i);
        // debug(s, t);

        REP(j, n) {
            if(s[j] and t[j]) G.add_edge_bidirectionally(i, j);
        }
    }

    print(G.count_components());

    return 0;
}
