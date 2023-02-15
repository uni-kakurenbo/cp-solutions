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

#include "data_structure/wavelet_matrix.hpp"

signed main() {
    int n; cin >> n;
    vector<int> p(n); input >> p;
    REP(n-1) cin.ignore();

    lib::wavelet_matrix<ll> data(ALL(p));

    int ans = 0;

    auto dfs = [&](auto&& dfs, int l, int r, int now, int cnt) {
        debug(l, r);

        auto mx = data.range(l, r).kth_largest_element(1);
        int ind = mx - data.begin();
        debug(ind);

        if(now < ind) chmin(r, ind);
        if(now > ind) chmax(l, ind+1);

        dfs(dfs, l, r, now, cnt+1);
        chmax(ans, cnt);
    };

    dfs(dfs, 0, n, data.select(n, 0), 0);

    print(ans);

    return 0;
}
