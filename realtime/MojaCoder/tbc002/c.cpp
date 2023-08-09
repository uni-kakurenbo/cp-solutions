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

#include "data_structure/disjoint_sparse_table.hpp"
#include "data_structure/range_action/range_sum.hpp"

using mint = lib::modint1000000007;

namespace std {

array<int,25> operator+(const array<int,25>& p, const array<int,25>& q) {
    array<int,25> res; res.fill(0);
    REP(i, 25) res[i] = p[i] + q[i];
    return res;
}

}

void solve() {
    int n, q; cin >> n >> q;
    valarray<i64> a(n); input >> a;

    lib::prime_sieve primes(100);
    debug(primes.size());

    valarray<std::array<int,25>> G(n);
    REP(i, n) {
        G[i].fill(0);
        REP(j, 25) {
            int p = primes[j];
            while(a[i] % p == 0) a[i] /= p, G[i][j]++;
        }
    }
    debug(G);

    lib::disjoint_sparse_table<lib::actions::range_sum<std::array<int,25>>> cnt(ALL(G));
    debug(cnt);

    REP(q) {
        int w, x, y, z; cin >> w >> x >> y >> z; --w, --y;
        auto res0 = cnt(w, x).fold();
        auto res1 = cnt(y, z).fold();
        debug(res0, res1);
        mint res = 1;
        REP(i, 25) res *= mint{primes[i]}.pow(lib::min(res0.val()[i], res1.val()[i]));
        print(res);
    }
}
