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
    int w, h; std::cin >> w >> h;
    int n; cin >> n;
    valarray<spair<i64>> ps(n); input >> ps;
    int x; input >> x;
    std::deque<int> a(x); input >> a;
    int y; input >> y;
    std::deque<int> b(y); input >> b;

    a.push_front(0), b.push_front(0);
    a.push_back(w), b.push_back(h);

    map<spair<int>,int> cnt;
    REP(i, n) {
        auto [ p, q ] = ps[i];
        int s = std::lower_bound(ALL(a), p) - a.begin();
        int t = std::lower_bound(ALL(b), q) - b.begin();
        cnt[{ s, t }]++;
    }
    debug(cnt);

    int ans0 = INF32, ans1 = 0;

    ITR(pos, v, cnt) {
        chmin(ans0, v);
        chmax(ans1, v);
    }

    if((i64)cnt.size() < (x + 1LL) * (y + 1)) ans0 = 0;

    print(ans0, ans1);
}
