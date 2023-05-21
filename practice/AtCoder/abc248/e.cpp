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
    int n, k; cin >> n >> k;

    using point = lib::point<i64>;
    valarray<point> ps(n); input >> ps;
    debug(ps);

    if(k == 1) {
        print("Infinity");
        return;
    }

    using mint = lib::modint1000000007;

    map<spair<int>,int> cnt;

    REP(i, n) {
        auto p = ps[i];
        REP(j, i+1, n) {
            debug(i, j);

            auto q = ps[j];

            i64 dx_pq = p.x() - q.x(), dy_pq = p.y() - q.y();

            mint slp = mint{dx_pq} == 0 ? mint{-1} : mint{dy_pq} / dx_pq;
            mint slc = mint{dx_pq} == 0 ? p.x() : slp * -p.x() + p.y();

            cnt[{(slp + INF32).pow(INF32).val(), (slc + INF32).pow(INF32).val()}]++;
        }
    }
    debug(cnt);

    print(std::count_if(ALL(cnt), [&](auto& p) { return p.second >= k * (k - 1) / 2; }));
}
