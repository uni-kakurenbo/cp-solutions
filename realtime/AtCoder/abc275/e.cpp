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
#include "grid.hpp"

using mint = atcoder::modint998244353;

signed main() {
    int n, m, k; cin >> n >> m >> k;

    mint inv_m = mint{1} / m;

    auto adv = [&n](int p, int x) {
        return p+x>n ? n-(p+x-n) : p+x;
    };

    UnfoldedGrid<mint> dp(k+1, n+1); // dp[i][j] := i 回目, マス j

    REP(i, k+1) dp(i, n) = 1;
    REPD(i, k) REPD(j, n) FOR(x, 1, m) {
        dp(i, j) += inv_m * dp(i+1, adv(j, x));
    }

    print(dp(0, 0));

    return 0;
}
