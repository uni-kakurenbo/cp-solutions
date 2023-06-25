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

#include "data_structure/bit_vector.hpp"

void solve() {
    i64  n; cin >> n;

    lib::bit_vector bits(1'000'000'001);

    i64 prev = 0;
    REP(i, n) {
        i64 a; cin >> a;
        if(i == 0) continue;
        if(i%2 == 0) REP(j, prev, a) bits.set(j);
        else prev = a;
    }

    bits.build();

    i64 q; cin >> q;
    REP(q) {
        i64 l, r; cin >> l >> r;
        print(bits.rank1(r) - bits.rank1(l));
    }
}
