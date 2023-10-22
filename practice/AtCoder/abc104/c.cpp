/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int d, g; cin >> d >> g; g /= 100;
    valarray<int> p(d), c(d); input >> lib::views::zip(p, c); c /= 100;

    int ans = INF32;
    valarray<int> r(d); std::iota(ALL(r), 0);
    do {
        debug(r);
        int cur = 0, sum = 0;
        bool det = false;
        ITR(i, r) {
            if(sum + (i + 1) * p[i] > g) {
                chmin(ans, cur + lib::max(0, lib::div_ceil<int>(g - sum, i + 1)));
                det = true;
                break;
            }
            sum += (i + 1) * p[i], cur += p[i];
            sum += c[i];
            debug(i, sum, cur);
        }
        if(not det) chmin(ans, cur);
    } while(std::next_permutation(ALL(r)));

    print(ans);
}
