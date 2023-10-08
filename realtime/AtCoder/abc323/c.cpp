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
    int n, m; cin >> n >> m;
    valarray<i64> a(m); input >> a;
    lib::grid<char,string> G(n, m); input >> G;

    valarray<i64> p(n);
    REP(i, n) {
        REP(j, m) {
            p[i] += (G(i, j) == 'o') * a[j];
        }
        p[i] += i + 1;
    }
    debug(p);

    valarray<int> id(m); std::iota(ALL(id), 0);
    id.sort([&](int i, int j) { return a[i] > a[j]; });
    debug(id);

    i64 max = p.max();
    REP(i, n) {
        i64 rem = max - p[i];
        debug(i, rem);
        if(rem == 0) {
            print(0);
            continue;
        }
        {
            i64 cur = 0;
            int cnt = 0;
            REP(j, m) {
                if(G(i, id[j]) == 'o') continue;
                cur += a[id[j]];
                cnt++;
                if(cur > rem) {
                    print(cnt);
                    break;
                }
            }
        }
    }
}
