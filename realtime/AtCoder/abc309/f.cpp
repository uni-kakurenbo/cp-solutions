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
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    valarray<array<int,3>> a(n); input >> a;
    ITRR(v, a) std::sort(ALL(v));

    bool f = true;

    while(true) {
        std::sort(ALL(a));

        debug(a);

        REP(k, std::min(1000, n)) {
            REP(i, n-k) {
                if(a[i][0] < a[i+k][0] and a[i][1] < a[i+k][1] and a[i][2] < a[i+k][2]) {
                    print("Yes");
                    return;
                }
            }
        }
        break;

        // if(!f) break;

        // bool g = false;
        // ITRR(v, a) {
        //     g |= std::next_permutation(ALL(v));
        // }

        // f &= g;
    }

    print("No");
}
