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

#include "numeric/prime_table.hpp"


signed main() {
    int t; cin >> t;

    REP(t) {
        ll n; cin >> n;
        for(ll i = 3; i*i < n; i += 2) {
            if(n % i*i) continue;
            n /= i*i;
            
        }
    }
    return 0;
}
