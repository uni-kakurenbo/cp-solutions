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

valarray<i64> t, d, e;

void solve() {
    int n; cin >> n;
    t.resize(n), d.resize(n);
    input >> lib::views::zip(t, d);
    e = d + t;

    struct comp {
        inline bool operator()(int i, int j) {
            return e[i] > e[j];
        }
    };

    std::priority_queue<int,std::vector<int>,comp> pq;

    valarray<int> inds(n); std::iota(ALL(inds), 0);
    inds.sort([&](int i, int j) { return t[i] < t[j]; });

    i64 ans = 0;
    i64 now = 0;

    int i = 0;
    while(true) {
        do {
            now = t[inds[i]];
            pq.push(inds[i++]);
            if(i >= n) break;
        } while(t[inds[i]] <= now);

        debug(i, now, pq.top());

        ans += now <= e[pq.top()];
        pq.pop();

        if(i >= n) break;
    }

    print(ans);
}
