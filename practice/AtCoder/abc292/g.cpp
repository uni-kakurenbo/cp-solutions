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
/* #endregion */

#include "numeric/matrix.hpp"
#include "numeric/modint.hpp"

using mint = lib::modint998244353;

signed main() {
    int n, m; cin >> n >> m;
    vector<string> s(n); input >> s;

    auto dp = lib::matrix<mint>::identity(n+1, 1);
    REP(i, n) dp(i,i+1) = 1;

    REPD(i, m) {
        auto a = lib::matrix<mint>::identity(n+1);
        REP(d, 10) {
            auto b = dp;
            FOR(l, n) FOR(r, l+1, n) {
                REP(j, l, r) {
                    if(s[j][i] != d+'0' and s[j][i] != '?') b[l][r] = 0;
                }
            }
            a *= b;
        }
        dp = a;
    }
    debug(dp);

    print(dp(0,n));

    return 0;
}
