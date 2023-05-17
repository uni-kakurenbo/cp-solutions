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

#include "iterable/inverse.hpp"

void solve() {
    int n, k; cin >> n >> k; --k;
    valarray<int> a(n); input >> a; a -= 1;
    lib::inverse inv(ALL(a));

    set<i64> unused(ALL(a));

    int cnt = 0;

    REP(i, n) {
        int p = 0;
        ITR(v, unused) {
            debug(v);
            bool f = v == a[i];
            if(f) {
                int m = n - i - 1;
                cnt += (m - 1) * m / 2 + n;
            }
            else {
                cnt++;
            }
            debug(cnt);

            if(cnt > k) {
                debug("over");
                if(!f or i == n - 1) {
                    a += 1;
                    std::reverse(a.begin() + i, a.begin() + inv[v][0] + 1);
                    print(a);
                    return;
                }
                unused.remove(v);
                int m = n - i - 1;
                cnt -= (m - 1) * m / 2 + n;
                break;
            }
        }
    }
}
