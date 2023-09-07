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
    int n, k; cin >> n >> k;
    valarray<spair<i64>> dt(n); input >> dt;
    ITRR(t, d, dt) std::swap(t, d);
    dt.sort().reverse();

    valarray<i64> used(n+1);
    std::priority_queue<spair<i64>,std::vector<spair<i64>>,std::greater<spair<i64>>> p;
    std::priority_queue<spair<i64>> q;

    i64 ans = 0;
    i64 now = 0;

    REP(i, k) {
        if(used[dt[i].second]) p.push(dt[i]);
        used[dt[i].second]++;
        now += dt[i].first;
    }

    REP(i, n) {
        if(used[dt[i].second] > 0) continue;
        q.push(dt[i]);
    }

    i64 x = used.count_if([&](int v) { return v >= 1; });

    ans = now + x * x;

    while(true) {
        while(not p.empty() and used[p.top().second] <= 1) p.pop();
        if(p.empty()) break;

        used[p.top().second]--;
        now -= p.top().first;
        p.pop();

        while(not q.empty() and used[q.top().second] > 0) q.pop();
        if(q.empty()) break;

        used[q.top().second]++;
        now += q.top().first;
        q.pop();

        x++;
        chmax(ans, now + x * x);
    }

    print(ans);
}
