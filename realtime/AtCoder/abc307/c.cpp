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
    int ha, wa; cin >> ha >> wa;
    lib::grid<char,string> a(ha, wa); input >> a;
    int hb, wb; cin >> hb >> wb;
    lib::grid<char,string> b(hb, wb); input >> b;
    int hx, wx; cin >> hx >> wx;
    lib::grid<char,string> x(hx, wx); input >> x;

    debug(a, b, x);

    REP(ia, -hx, hx) REP(ja, -wx, wx) {
        REP(ib, -hx, hx) REP(jb, -wx, wx) {
            lib::grid<char,string> c(hx, wx, '.');;
            REP(i, ha) REP(j, wa) {
                int ii = ia + i;
                int jj = ja + j;
                if(a[i][j] == '#') {
                    if(0 <= ii and ii < hx and 0 <= jj and jj < wx) c(ii, jj) = '#';
                    else {
                        goto skip;
                    }
                }
            }
            REP(i, hb) REP(j, wb) {
                int ii = ib + i;
                int jj = jb + j;
                if(b[i][j] == '#') {
                    if(0 <= ii and ii < hx and 0 <= jj and jj < wx) c(ii, jj) = '#';
                    else {
                        goto skip;
                    }
                }
            }
            if(x == c) {
                print("Yes");
                return;
            }
            skip:;
            debug(ia, ja, ib, jb, c);
        }
    }

    print("No");
}
