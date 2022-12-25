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

namespace atcoder {}
using namespace atcoder;

namespace Lib {}
using namespace Lib;

#include "template.hpp"
/* #endregion */

#include "iterable/accumulation.hpp"

#include <atcoder/segtree>

ll op(const ll a, const ll b) { return max(a, b); }
ll e() { return INT64_MIN; }

signed main() {
    int n, m; cin >> n >> m;

    vector<ll> diff(n+1);
    REP(m) {
        ll a, b; cin >> a >> b; --a;
        ++diff[a], --diff[b];
    }

    Lib::Accumulation<ll> table(ALL(diff));
    table.erase(table.begin());
    debug(table);

    vector<vector<int>> rev(m+1);
    REP(i, n) rev[table[i]].push_back(i);
    debug(rev);

    segtree<ll,op,e> range_max(table);

    int q; cin >> q;
    REP(q) {
        int l, r; cin >> l >> r; --l;
        int k = range_max.prod(l, r);
        debug(k);
        int res = lower_bound(ALL(rev[k]), r) - lower_bound(ALL(rev[k]), l);
        print(res);
    }


    return 0;
}
