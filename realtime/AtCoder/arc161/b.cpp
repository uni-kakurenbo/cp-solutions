/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/bit.hpp"

void solve() {
    u64 n; cin >> n;
    debug(lib::base_n_string(n, 2));

    int pop = 0;

    while(true) {
        pop = __builtin_popcountll(n);
        if(pop >= 3) break;
        n--;
        if(n <= 0) {
            print(-1);
            return;
        }
    }
    debug(lib::base_n_string(n, 2));

    debug(pop, n);

    u64 ans = 0;

    int cnt = 0;
    REPD(i, 63) {
        if((n >> i) & 1) {
            ans |= 1UL << i;
            cnt++;
        }
        if(cnt >= 3) break;
    }
    debug(lib::base_n_string(ans, 2));

    print(ans);
}
