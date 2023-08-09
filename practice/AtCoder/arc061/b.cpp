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
    int h, w, n; cin >> h >> w >> n;
    valarray<spair<i64>> p(n); input >> p;
    ITRR(i, j, p) --i, --j;
    lib::set<spair<i64>> st(ALL(p));
    debug(p);

    lib::set<spair<i64>> check;
    ITR(i, j, p) {
        FOR(di, -2, 0) FOR(dj, -2, 0) {
            int ni = i + di, nj = j + dj;
            if(0 <= ni && ni+3 <= h and 0 <= nj && nj+3 <= w) check.emplace(ni, nj);
        }
    }
    debug(check);

    array<i64,10> ans; ans.fill(0);

    ITR(i, j, check) {
        int cnt = 0;
        REP(di, 3) REP(dj, 3) {
            int ni = i + di, nj = j + dj;
            cnt += st.count({ ni, nj });
        }
        debug(i, j, cnt);
        ans[cnt]++;
    }

    ans[0] = 1UL * (h - 2) * (w - 2) - lib::sum(ans);

    print(ans);
}
