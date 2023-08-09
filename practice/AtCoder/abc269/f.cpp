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

#include "numeric/numerical_sequence.hpp"

using mint = lib::modint998244353;

namespace ns = lib::numerical_sequence;
using row = ns::arithmetic<mint>;
using cdiff = ns::common_difference<mint>;
using zeroth = ns::static_term<mint,0>;

void solve() {
    i64 n, m; cin >> n >> m;

    auto f = [&](mint i, mint j) { return i * m + j + 1; };

    int q; cin >> q;
    REP(q) {
        int a, b, c, d; cin >> a >> b >> c >> d; --a, --c;

        row line0, line1;
        i64 m0, m1; m0 = m1 = (d - c) / 2;

        if((a + c) % 2 == 0) {
            line0 = row(zeroth(f(a, c)), cdiff(2));
            line1 = row(zeroth(f(a + 1, c + 1)), cdiff(2));
            m0 = (d - c + 1) / 2;
        }
        else {
            line0 = row(zeroth(f(a, c + 1)), cdiff(2));
            line1 = row(zeroth(f(a + 1, c)), cdiff(2));
            m1 = (d - c + 1) / 2;
        }

        zeroth beg0(line0.sum(m0)), beg1(line1.sum(m1));
        row sum0(beg0, cdiff(2*m*m0)), sum1(beg1, cdiff(2*m*m1));

        print(sum0.sum((b - a + 1) / 2) + sum1.sum((b - a) / 2));
    }
}
