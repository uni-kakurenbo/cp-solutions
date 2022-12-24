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
using mint = atcoder::modint998244353;

#include "multi_container.hpp"

signed main() {
    int n; cin >> n;
    vector<ll> a(n); REP(i, n) cin >> a[i];

    mint ans = 0;
    FOR(i, 1, n) {
        MultiVector<mint,3> dp(n+1, i+2, i);
        dp(0, 0, 0) = 1;
        REP(j, n) FOR(k, 0, i) REP(l, i) {
            dp(j+1, k, l) += dp(j, k, l);
            dp(j+1, k+1, mod(l+a[j], i)) += dp(j, k, l);
        }
        ans += dp(n, i, 0);
    }

    print(ans);

    return 0;

}
