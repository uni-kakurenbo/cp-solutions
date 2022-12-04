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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

#include "iterable/counter.hpp"

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;

    ITRR(v, a) v %= 200;
    Lib::Counter<int> cnt(ALL(a));

    ll ans = 0;
    REP(p, 200) ans += 1LL * cnt[p]*(cnt[p] - 1);
    ans /= 2;

    print(ans);

    return 0;
}
