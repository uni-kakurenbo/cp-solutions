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

#include "iterable/accumulation.hpp"
#include "numeric/interval_scanner.hpp"

signed main() {
    string s; cin >> s;
    int k; cin >> k;

    vector<bool> a(size(s));
    REP(i, size(s)) a[i] = s[i] == '.';

    Accumulation sum(ALL(a), 0);

    int cnt = 0;
    auto validate = [&](auto) { return true; };
    auto init = [&]() { cnt = 0; };
    auto valid = [&]() { return cnt <= k; };
    auto expand = [&](auto val) { cnt += *val; };
    auto contract = [&](auto val) { cnt -= *val; };

    int ans = 0;
    auto apply = [&](auto l, auto r) { chmax(ans, r - l); };

    InclusiveIntervalScanner<vector<bool>::iterator> scanner(validate, init, valid, expand, contract, apply);
    scanner.scan_all(ALL(a));

    print(ans);

    return 0;
}
