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
    int n, k; cin >> n >> k;
    vector<i64> p(n); input >> p;

    valarray<i64> bound(n, n);
    REPD(i, n-1) {
        if(p[i] < p[i+1]) bound[i] = bound[i+1];
        else bound[i] = i + 1;
    }
    debug(bound);

    auto q = p;
    std::sort(q.end() - k, q.end());
    debug(q);

    valarray<int> lmin(n + 1, INF32);
    REP(i, n - k, n) chmin(lmin[i + 1], lmin[i], p[i]);
    debug(lmin);

    REP(i, n - k) {
        if(bound[i] >= i + k) {
            print(p);
            return;
        }
        if(bound[i] >= n - k and lmin[i + k] > p[n - k - 1]) {
            auto r = p;
            std::sort(r.begin() + i, r.begin() + (i + k));
            debug(r);
            print(std::max(r, q));
            return;
        }
    }

    print(q);
}
