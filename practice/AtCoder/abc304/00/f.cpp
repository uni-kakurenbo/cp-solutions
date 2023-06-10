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

#include <boost/dynamic_bitset.hpp>
#include <boost/lexical_cast.hpp>

#include "numeric/prime.hpp"

using mint = lib::modint998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    boost::dynamic_bitset<> needs(n);
    REP(i, n) needs[i] = s[i] == '.';

    debug(s, boost::lexical_cast<std::string>(needs));

    valarray<mint> res(n);

    REP(dv, 1, n) {
        if(n%dv != 0) continue;
        debug(dv);

        auto cp = needs;
        boost::dynamic_bitset<> put(n); REP(i, dv) put.set(i);
        boost::dynamic_bitset<> msk(n);

        REP(n/dv) {
            msk |= cp & put;
            cp >>= dv;
        }

        int cnt = 0;
        REP(i, dv) cnt += !msk[i];

        res[dv] = mint{2}.pow(cnt);
        REP(d, 1, dv) if(dv%d == 0) res[dv] -= res[d];
    }

    print(res.sum());
}
