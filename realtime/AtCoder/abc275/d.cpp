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

signed main() {
    ll n; cin >> n;

    map<ll,ll> memo;
    auto dfs = [&](auto& dfs, ll k) {
        if(k == 0) return 1LL;
        if(memo.count(k)) return memo[k];
        return memo[k] = dfs(dfs, k / 2) + dfs(dfs, k / 3);
    };

    print(dfs(dfs, n));

    return 0;
}
