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
    int n, m; cin >> n >> m;
    valarray<i64> a(n), b(n); input >> lib::views::zip(a, b);
    a -= 1, b -= 1;
    lib::inverse inv(ALL(a));
    REP(i, n) inv[b[i]].push_back(i);
    debug(inv);

    valarray<i64> cnt(n), ans(m + 1);
    int zero = n, r = 0;
    REP(l, m) {
        while(r < m and zero != 0) {
            ITR(x, inv[r]) {
                if(cnt[x] == 0) zero--;
                cnt[x]++;
            }
            r++;
        }
        if(zero != 0) break;
        ans[r - l - 1]++, ans[m - l]--;
        ITR(x, inv[l]) {
            cnt[x]--;
            if(cnt[x] == 0) zero++;
        }
    }

    REP(i, m) ans[i+1] += ans[i];
    print(ans.begin(), ans.end() - 1);
}
