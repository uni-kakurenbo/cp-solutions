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

#include "numeric/prime.hpp"

signed main() {
    ll n; cin >> n;

    auto facts = lib::factorize(n);

    int ans = 0;

    ITR(fact, cnt, facts) {
        int p = 0, i = 1;
        while(true) {
            if(i * (i + 1) / 2 <= cnt) p = i++;
            else break;
        }
        ans += p;
    }

    print(ans);

    return 0;
}
