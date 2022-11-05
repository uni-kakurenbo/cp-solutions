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
    int n, x, y; cin >> n >> x >> y;
    vector<int> a(n); REP(i, n) cin >> a[i];

    ll ans = 0;
    int cnt_x = 0, cnt_y = 0;
    auto validate = [&](auto itr) { return y <= *itr and *itr <= x; };
    auto init = [&]() { cnt_x = 0, cnt_y = 0; };
    auto valid = [&]() { return cnt_x and cnt_y; };
    auto expand = [&](auto itr) {
        if(*itr == x) ++cnt_x;
        if(*itr == y) ++cnt_y;
    };
    auto contract = [&](auto itr) {
        if(*itr == x) --cnt_x;
        if(*itr == y) --cnt_y;
    };

    auto last = a.end();
    auto apply = [&](auto, auto r) { ans += last - r + 1; };

    InclusiveIntervalScanner<vector<int>::iterator> scanner(validate, init, valid, expand, contract, apply);
    InclusiveIntervalScanner<vector<int>::iterator>::Intervals targets;
    scanner.split(ALL(a), &targets);

    ITRM(start, end, targets) {
        last = end;
        scanner.scan<true>(start, end);
    }

    print(ans);

    return 0;
}
