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

#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;

signed main() {
    int n; cin >> n;
    vector<ll> x(n), y(n);
    REP(i, n) cin >> x[i] >> y[i];

    vector<mint> fact(500000), inv_fact(500000);
    fact[0] = 1;
    inv_fact[0] = 1;
    REPF(i, 1, 500000) {
        fact[i] = fact[i-1] * i;
        inv_fact[i] = mint{1} / fact[i];
    }
    // debug(fact, inv_fact);

    vector<ll> p(n);
    iota(ALL(p), 0);

    mint ans = 0;
    ll min_dist = INF64;
    do {
        mint prod = 1;
        ll px = 0, py = 0;
        ll dist = 0;
        ITR(i, p) {
            ll dx = abs(px - x[i]), dy = abs(py - y[i]);
            prod *= fact[dx+dy] * inv_fact[dx] * inv_fact[dy];
            px = x[i], py = y[i];
            dist += dx + dy;
        }
        px = abs(px), py = abs(py);
        dist += px + py;
        prod *= fact[px+py] * inv_fact[px] * inv_fact[py];
        // debug(prod);
        if(min_dist > dist) {
            min_dist = dist;
            ans = 0;
        }
        if(min_dist == dist) {
            ans += prod;
            debug(p, min_dist, dist, prod);
        }
    } while(next_permutation(ALL(p)));

    debug(min_dist);

    print(ans);

    return 0;
}
