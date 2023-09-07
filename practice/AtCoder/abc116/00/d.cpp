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

void solve() {
    i64 n, k; cin >> n >> k;
    valarray<i64> t(n), d(n); input >> lib::views::zip(t, d);

    valarray<i64> a(n); std::iota(ALL(a), 0);
    a.sort([&](i64 i, i64 j) { return d[i] > d[j]; });

    valarray<i64> e(n); REP(i, n) e[i] = d[a[i]];
    lib::accumulation cum(ALL(e));
    debug(e, cum);

    valarray<i64> ans(k);
    lib::set<i64> st;
    i64 st_sum = 0;
    valarray<i64> rest_sum(n+1);

    i64 cnt = 0;
    REP(j, n) {
        i64 i = a[j];
        if(st.contains(t[i])) {
            rest_sum[j - cnt + 1] = rest_sum[j - cnt] + d[i];
            continue;
        }
        st.insert(t[i]);
        st_sum += d[i];
        i64 r = lib::min(k - cnt - 1, j - cnt);
        if(r >= 0) ans[cnt] += rest_sum[r];
        ans[cnt] += st_sum + lib::pow(cnt+1, 2);
        if(k - cnt - r - 1 >= 0) ans[cnt] += cum(j+1, lib::min(n, j + k - cnt - r));

        debug(rest_sum);
        debug(st, st_sum, j, r, j - cnt, k - cnt - r);
        cnt++;
        if(cnt >= k) break;
    }

    debug(ans);

    print(ans.max());
}
