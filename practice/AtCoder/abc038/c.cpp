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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "numeric/interval_scanner.hpp"

signed main() {
    int n;; cin >> n;

    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    int last = 0;
    auto validate = [&](auto) { return true; };
    auto init = [&](auto itr) { last = *itr; };
    auto can_expand = [&](auto itr) { return last < *itr; };
    auto expand = [&](auto itr) { last = *itr; };
    auto contract = [&](auto) { };

    ll ans = 0;
    auto apply = [&](auto l, auto r) { ans += r - l; };

    ExclusiveIntervalScanner<vector<ll>::iterator> scanner(validate, init, can_expand, expand, contract, apply);
    scanner.scan_all(ALL(a));

    print(ans);
}
