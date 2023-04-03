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

#include "numeric/interval_scanner.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a; a -= 1;

    int q; cin >> q;
    vector<spair<int>> qs(q); input >> qs;
    REP(i, q) qs[i].first--;

    vector<i64> cnt(n);
    i64 ans = 0;

    auto expand = [&](int p) {
        int v = a[p];
        cnt[v]++;
        if(cnt[v]%2 == 0) ans++;
    };
    auto contract = [&](int p) {
        int v = a[p];
        cnt[v]--;
        if(cnt[v]%2 == 1) ans--;
    };
    auto eval = [&]() { return ans; };

    debug(qs);

    auto res = lib::interval_scan(expand, contract, eval, ALL(qs));
    print(res);
}
