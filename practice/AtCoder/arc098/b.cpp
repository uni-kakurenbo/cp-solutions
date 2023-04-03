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
    vector<int> a(n); REP(i, n) cin >> a[i];

    ll ans = 0, sum = 0;

    auto validate = [&](auto) { return true; };
    auto init = [&](auto itr) { sum = *itr;};
    auto expandable = [&](auto itr) { return (sum + *itr) == (sum ^ *itr); };
    auto expand = [&](auto itr) { sum += *itr; };
    auto contract = [&](auto itr) { sum -= *itr; };
    auto apply = [&](auto l, auto r) { ans += r - l; };

    lib::exclusive_interval_scanner<vector<int>::iterator> scanner(validate, init, expandable, expand, contract, apply);
    scanner.scan_all(ALL(a));

    print(ans);
}
