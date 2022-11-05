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

ll f(ll a, ll b){
  return a*a*a + a*a*b + a*b*b + b*b*b;
}

signed main() {
    ll n; cin >> n;

    constexpr ll MAX = 1000001;
    ll a = 0, b = MAX, ans = INF64;
    auto validate = [&](auto) { return true; };
    auto init = [&]() { a = 0, b = MAX; };
    auto valid = [&]() { return b >= 0 and f(a, b) >= n; };
    auto expand = [&](auto x) { a = x; };
    auto contract = [&](auto x) { b = MAX-x; };
    auto apply = [&](auto, auto) { chmin(ans, f(a, b)); };

    InclusiveIntervalScanner<ll> scanner(validate, init, valid, expand, contract, apply);
    scanner.scan_all<true,false>(0, MAX+1);

    print(ans);
}
