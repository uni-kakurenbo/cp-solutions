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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/range_set_range_sum.hpp"

signed main() {
    int n; cin >> n;
    vector<ll> a(n); input >> a;

    lib::lazy_segment_tree<lib::actions::range_set_range_sum<ll>> data(ALL(a));

    map<ll,stack<int>> ids;
    unordered_map<ll,set<ll>> ranges;

    REP(i, n) {
        ll v = a[i];

        if(ids[v].empty()) goto end;

        if()

        data.apply(ids[v].top(), i, v);
        last = { ids[v].top(), i };
        ids[v].pop();

      end:
        ids[v].push(i);
        debug(data);

    }

    ITR(v, data) cout << v << "\n";

    return 0;
}
