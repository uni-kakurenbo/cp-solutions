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
#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/range_set_range_sum.hpp"


signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;

    vector<int> b[2];
    REP(i, n) b[i%2].push_back(a[i]);

    std::sort(ALL(b[0])), std::sort(ALL(b[1]));
    vector<int> c(n);
    REP(i, n) c[i] = b[i%2][i/2];

    auto d = c;
    sort(ALL(d));
    if(d != c) {
        print(-1);
        return 0;
    }

    lib::compression<int> comp(ALL(a));

    lib::lazy_segment_tree<lib::actions::range_set_range_sum<int>> cnt(n);

    ll ans = 0;
    REP(i, 0, n, 2) {
        ans += cnt.prod(comp.rank(a[i])+1, n);
        cnt.set(comp.rank(a[i]), cnt[comp.rank(a[i])] + 1);
        debug(cnt);
    }
    cnt.set(0, n, 0);
    REP(i, 1, n, 2) {
        ans += cnt.prod(comp.rank(a[i])+1, n);
        cnt.set(comp.rank(a[i]), cnt[comp.rank(a[i])] + 1);
        debug(cnt);
    }

    print(ans);

    return 0;
}
