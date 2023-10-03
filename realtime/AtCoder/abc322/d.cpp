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
    lib::grid<char,string> minos[3];
    REP(i, 3) minos[i].resize(4, 4);
    input >> minos;
    debug(minos);

    FOR(ai, -3, 3) FOR(aj, -3, 3) REP(4) {
        minos[0].rotate();
        FOR(bi, -3, 3) FOR(bj, -3, 3) REP(4) {
            minos[1].rotate();
            FOR(ci, -3, 3) FOR(cj, -3, 3) REP(4) {
                minos[2].rotate();

                lib::grid<char,string> ord(4, 4, '.');

                REP(i, 4) REP(j, 4) {
                    int aii = i + ai, ajj = j + aj;
                    int bii = i + bi, bjj = j + bj;
                    int cii = i + ci, cjj = j + cj;

                    if(minos[0](i, j) == '#' and (not ord.is_valid(aii, ajj) or ord(aii, ajj) != '.')) goto ng;
                    if(minos[0](i, j) == '#') ord(aii, ajj) = '#';

                    if(minos[1](i, j) == '#' and (not ord.is_valid(bii, bjj) or ord(bii, bjj) != '.')) goto ng;
                    if(minos[1](i, j) == '#') ord(bii, bjj) = '#';

                    if(minos[2](i, j) == '#' and (not ord.is_valid(cii, cjj) or ord(cii, cjj) != '.')) goto ng;
                    if(minos[2](i, j) == '#') ord(cii, cjj) = '#';
                }

                REP(i, 4) REP(j, 4) {
                    if(ord(i, j) == '.') goto ng;
                }

                debug(ord);
                print("Yes");
                return;

                ng:;
            }
        }
    }

    print("No");
}
