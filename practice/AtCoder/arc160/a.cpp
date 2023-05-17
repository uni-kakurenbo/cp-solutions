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

void solve() {
    int n, k; cin >> n >> k; --k;
    valarray<int> a(n); input >> a;

    vector<spair<int>> ps;
    REP(i, n) REP(j, i, n) ps.emplace_back(i, j);

    std::nth_element(ps.begin(), ps.begin() + k, ps.end(), [&](auto p, auto q) {
        if(p.first == q.first) return a[p.second] < a[q.second];
        if(p.first < q.first) {
            if(p.first == p.second) return a[q.first] < a[q.second];
            return a[p.second] < a[p.first];
        }
        if(q.first == q.second) return a[p.second] < a[p.first];
        return a[q.second] > a[q.first];
    });

    auto [ l , r ] = ps[k];
    std::reverse(a.begin() + l, a.begin() + r + 1);

    print(a);
}
