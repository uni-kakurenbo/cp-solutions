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
#include "graph/minimum_paph_cover.hpp"

signed main() {
    int n; cin >> n;

    vector<ll> X(n), E(n);
    REP(i, n) input >> X[i] >> E[i];
    debug(X, E);

    if(set(ALL(E)).size() == 1) {
        print(set(ALL(X)).size());
        return 0;
    }

    vector<int> XmE(n), XpE(n);
    iota(ALL(XmE), 0), iota(ALL(XpE), 0);

    auto compXmE = [&](int i, int j) { return X[i] - E[i] < X[j] - E[j]; };
    auto compXpE = [&](int i, int j) { return X[i] + E[i] < X[j] + E[j]; };

    sort(ALL(XmE), compXmE);
    sort(ALL(XpE), compXpE);

    debug(XmE, XpE);

    vector<bitset<500000>> u(n);

    REP(i, n) {
        auto a = lower_bound(ALL(XmE), i, compXmE);
        auto b = upper_bound(ALL(XpE), i, compXpE);

        bitset<500000> s, t;
        REPD(i, a, XmE.end()) s.set(*i);
        REP(i, XpE.begin(), b) t.set(*i);

        u[i] = s & t;
    }

    bitset<500000> covd;
    REP(i, n) {
        covd |= *max_element(ALL(u), [](const auto& a, const auto& b) { return a.count() < b.count(); });

        if(covd.count() >= n) {
            print(i+1);
            return 0;
        }

        REP(i, n) u[i] &= ~covd;
    }

    return 0;
}
