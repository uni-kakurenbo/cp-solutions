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
    i64 n, l; cin >> n >> l;
    valarray<i64> a(n); input >> a;
    std::priority_queue<i64,std::vector<i64>,std::greater<i64>> pq(ALL(a));

    i64 sum = a.sum();
    if(sum < l) pq.push(l - sum);

    i64 ans = 0;

    while(pq.size() > 1) {
        i64 x = pq.top(); pq.pop();
        i64 y = pq.top(); pq.pop();
        pq.push(x + y);
        ans += x + y;
    }

    print(ans);
}
