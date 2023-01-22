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
#include "iterable/compression.hpp"
#include "iterable/run_length_encoding.hpp"

signed main() {
    ll n; cin >> n;
    string s; cin >> s;

    lib::compression<char> comp(ALL(s));
    lib::run_length<ll> t(ALL(comp));
    debug(t);

    int vs = set(ALL(comp)).size();

    map<pair<ll,ll>,ll> move;
    REP(i, t.size()-1) {
        ll x = t[i].first, y = t[i+1].first;
        ++move[{ x, y }];
    }
    debug(move);


    vector<lib::grid<ll>> costs;
    vector<ll> p(vs); iota(ALL(p), 0);
    int k = 0;
    do {
        costs.emplace_back(lib::grid<ll>(vs, vs));

        REP(i, vs) REP(j, i+1, vs) {
            ll diff = find(ALL(p), i) - find(ALL(p), j);
            costs[k][i][j] = costs[k][j][i] = diff;
        }
        ++k;
    } while(next_permutation(ALL(p)));

    ll q; cin >> q;
    REP(i, q) {
        ll a, l, r; cin >> a >> l >> r;

        ll min_cost = LONG_LONG_MAX;
        ITR(f, costs) {
            ll cost = 0;

            ITR(x, c, move) {
                int d = x.first - x.second;
                int cc = f[x.first][x.second];
                cost += abs(cc) * ((cc < 0) xor (d < 0) ? l : r) * c;
            }

            debug(cost);
            chmin(min_cost, cost);
        }
        print(a * n + min_cost);
    }

    return 0;
}
