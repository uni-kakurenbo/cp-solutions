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
    int n; ll k; cin >> n >> k;

    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    if (find(a.begin(), a.end(), 0ll) != a.end()) {
        cout << n << endl;
        return 0;
    }

    ll prod = 1;
    auto validate = [&](auto itr) { return *itr <= k; };
    auto init = [&]() { prod = 1; };
    auto valid = [&]() { return prod <= k; };
    auto expand = [&](auto itr) { prod *= *itr; };
    auto contract = [&](auto itr) { debug(prod, *itr), assert(prod % *itr == 0), prod /= *itr; };

    int ans = 0;
    auto apply = [&](auto l, auto r) { chmax(ans, r - l); };

    Lib::InclusiveIntervalScanner<vector<ll>::iterator> scanner(validate, init, valid, expand, contract, apply);
    scanner.scan_all(ALL(a));

    print(ans);
}
