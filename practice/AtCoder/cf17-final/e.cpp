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
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::static_modint<26>;

void solve() {
    string s; cin >> s;
    int m = s.size();

    valarray<i64> v(m + 2);
    REP(i, m) v[i+1] = s[i] - 'a';

    lib::adjacent_difference diff(ALL(v));

    debug(v, diff);

    lib::dsu ds(m + 1);

    REP(i, m) ds.merge(i, m-i);

    int n; cin >> n;
    REP(n) {
        i64 l, r; cin >> l >> r; --l;
        ds.merge(l, r);
    }

    auto groups = ds.groups();

    ITR(group, groups) {
        mint ans = 0;
        ITR(v, group) ans += diff[v];
        if(ans != 0) {
            print("NO");
            return;
        }
    }

    print("YES");
}
