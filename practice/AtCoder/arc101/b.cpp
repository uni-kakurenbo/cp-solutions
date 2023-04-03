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

#include "iterable/compression.hpp"

#include "numeric/boundary_seeker.hpp"
#include "data_structure/fenwick_tree.hpp"
#include "data_structure/range_action/range_sum.hpp"

signed main() {
    i64 n; cin >> n;
    vector<i64> a(n); input >> a;
    auto b = lib::sorted(ALL(a));
    debug(b);

    auto ok = [&](int p) {
        i64 v = b[p];
        debug(p, v);

        std::vector<int> c(n), s(n+1);
        REP(i, n) c[i] = (a[i] < v ? -1 : 1);
        REP(i, n) s[i+1] = s[i] + c[i];
        debug(c, s);

        lib::compression<int> comp(ALL(s));
        debug(comp);

        lib::fenwick_tree<lib::actions::range_sum<i64>> cnt(n+1);
        i64 res = 0;
        REP(i, n+1) {
            res += cnt.prod(0, comp[i]+1);
            cnt.apply(comp[i], 1);
        }
        debug(res, (n*(n+1)+3)/4);
        return res >= (n*(n+1)+3)/4;
    };

    lib::boundary_seeker<int> seeker(ok);
    int v = seeker.bound(0, n);

    print(b[v]);

    return 0;
}
