/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

#include "numeric/modint.hpp"
#include "numeric/prime.hpp"

signed main() {
    ll n, k; input >> n >> k;
    std::vector<int> a(n); input >> a;

    std::valarray<int> cnt(k);
    REP(i, n) cnt[a[i] % k]++;
    debug(cnt);

    ll ans = 0;
    REP(i, 1LL, k) {
        ll p = i;
        while(p <= k) {
            ans += cnt[i] * cnt[p];
            p *= i;
        }
    }

    print(ans);

    return 0;
}
