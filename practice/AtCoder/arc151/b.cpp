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

#include "numeric/modint.hpp"
#include "data_structure/disjoint_set_union.hpp"

using mint = lib::modint998244353;

signed main() {
    ll n, m; cin >> n >> m;
    vector<ll> p(n); input >> p; REP(i, n) --p[i];

    mint ans = 0;
    int cnt = 0;
    lib::dsu dsu(n);

    REP(i, n) {
        if(dsu.same(i, p[i])) continue;
        dsu.merge(i, p[i]);
        ans += mint{m}.pow(n - ++cnt) * (m - 1) / 2;
    }

    print(ans);

    return 0;
}
