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

#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;

#include "iterable/accumulation.hpp"
#include "multi_vector.hpp"

signed main() {
    int n; cin >> n;
    vector<int> a(n); REP(i, n) cin >> a[i];
    Lib::Accumulation<int> sum(ALL(a));

    Lib::MultiVector<int,2> bounds(n, 0);

    REP(l, n) {
        FOR(r, l+1, n) {
            if(sum(l, r) % (r-l)) continue;
            bounds[l].push_back(r);
        }
    }

    mint ans = 0;
    REP(i, n) {
        ans += bounds[i].size();

    }


    return 0;
}
