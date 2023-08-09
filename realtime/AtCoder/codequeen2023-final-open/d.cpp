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
    i64 h, w, is, js, it, jt; cin >> h >> w >> is >> js >> it >> jt; --is, --js, --it, --jt;
    i64 n = std::max(h, w);

    i64 ans = 0;

    REP(a, 8) REP(k, 1, n) {
        i64 i = is + DIRS8[a].first * k;
        i64 j = js + DIRS8[a].second * k;
        if(i < 0 or j < 0 or i >= h or j >= w) continue;
        debug(i, j);
        REP(b, 8) REP(c, 8) {
            i64 d0 = DIRS8[b].first;
            i64 d1 = DIRS8[c].first;
            i64 d2 = DIRS8[b].second;
            i64 d3 = DIRS8[c].second;
            i64 p = d0*d3 - d1*d2;
            i64 q = d1*d2 - d0*d3;
            i64 x0 = (i - it) * d3;
            i64 y0 = (j - jt) * d1;
            i64 x1 = (i - it) * d2;
            i64 y1 = (j - jt) * d0;
            if(p == 0) {
                if(y0 - x0 == 0 and y1 - x1 == 0) {
                    if((i - it) * d0 == d2 * (j - jt)) {
                        if(b > c) continue;
                        debug(DIRS8[b], DIRS8[c]);
                        if(b == c) {
                            i64 o = std::max(std::abs(i - it), std::abs(j - jt));
                            if(o >= 2) {
                                debug(o - 1);
                                ans += o - 1;
                            }
                        }
                        else {
                            if(d0 == 0) {
                                ans += (w - i) - 2 + (i == it and j == jt);
                                debug(w - 2 + (i == it and j == jt));
                            }
                            else if(d1 == 0) {
                                ans += h - 2 + (i == it and j == jt);
                                debug(h - 2 + (i == it and j == jt));
                            }
                            else {
                                debug(std::min(h, w) - 2 + (i == it and j == jt));
                                ans += std::min(h, w) - 2 + (i == it and j == jt);
                            }
                        }
                    }
                }
            }
            else {
                if((y0 - x0) % p == 0 and (y1 - x1) % q ==0) {
                    i64 d00 = (y0 - x0) / p, d01 = (y1 - x1) / q;
                    if(d0 > 0 and d01 > 0) {
                        i64 ii = i + d0 * d00;
                        i64 jj = j + d2 * d00;
                        i64 iii = ii + d1 * d01;
                        i64 jjj = jj + d3 * d01;
                        if(ii < 0 or jj < 0 or iii < 0 or jjj < 0) continue;
                        if(ii >= h or jj >= w or iii >= h or jjj >= w) continue;
                        debug(DIRS8[b], DIRS8[c], d00, d01);
                        ans++;
                    }
                }
            }
        }
    }

    print(ans);
}
