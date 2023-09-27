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

#include "data_structure/disjoint_sparse_table.hpp"
#include "data_structure/range_action/range_min.hpp"

void solve() {
    int n, k; cin >> n >> k;
    valarray<i32> p(n); input >> p;

    lib::disjoint_sparse_table<lib::actions::range_min<i32>> min(ALL(p));

    valarray<int> ind(n - k + 1); std::iota(ALL(ind), 0);

    std::sort(RALL(ind), [&](const int i, const int j) {
        i32 a, b;
        if(i < j) {
            a = min(i, i + k).fold(), b = p[i];
            if(a == b) a = min(i + 1, i + k).fold(), b = p[i + 1];
        }
        else {
            a = p[j], b = min(j, j + k).fold();
            if(a == b) a = p[j + 1], b = min(j+1, j+k).fold();
        }
        return a < b;
    });
    debug(ind);

    sort(p.begin() + ind[0], p.begin() + ind[0] + k);

    print(p);
}
