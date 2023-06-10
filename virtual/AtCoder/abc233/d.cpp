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

#include "iterable/counter.hpp"

void solve() {
    i64 n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;
    lib::accumulation<i64> acc(ALL(a));

    std::map<i64,i64> cnt;

    i64 ans = 0;

    ITR(v, acc) {
        ans += cnt[v - k];
        cnt[v]++;
    }

    print(ans);
}
