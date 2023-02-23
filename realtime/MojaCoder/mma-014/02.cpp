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
    ll h, a; cin >> h >> a;

    for(;a;a--) {
        if(lib::is_prime(a)) {
            break;
        }
    }

    print((h + a - 1) / a);


    return 0;
}
