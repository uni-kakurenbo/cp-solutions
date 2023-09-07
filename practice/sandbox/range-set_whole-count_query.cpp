/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, q; cin >> n >> q;

    valarray<int> a(n);
    lib::set<int> indices; REP(i, n) indices.insert(i);

    valarray<std::tuple<int,int,int>> queries(q); input >> queries;
    queries.reverse();
    debug(queries);

    REP(i, q) {
        auto [ l, r, x ] = queries[i]; --l;
        for(auto itr = indices.lower_bound(l), end = indices.lower_bound(r); itr != end; ) {
            a[*itr] = x;
            itr = indices.erase(itr);
        }
        debug(indices);
    }

    print(a);
}
