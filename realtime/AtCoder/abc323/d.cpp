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
    int n; cin >> n;
    valarray<i64> s(n), c(n); input >> lib::views::zip(s, c);
    debug(s, c);

    valarray<i64> p(n), t(n);
    REP(i, n) {
        p[i] = lib::countr_zero<u64>(s[i]);
        t[i] += s[i] >> p[i];
    }
    debug(p, t);

    lib::map<i64,lib::array<i64,64>> mp;
    REP(i, n) mp[t[i]][p[i]] += c[i];
    debug(mp);


    ITRR(_, cnts, mp) {
        REP(i, 63) {
            cnts[i+1] += cnts[i] / 2;
            cnts[i] %= 2;
        }
    }
    debug(mp);

    i64 ans = 0;
    ITR(_, cnts, mp) ans += lib::sum(cnts);
    print(ans);
}
