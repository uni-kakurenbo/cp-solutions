/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    lib::grid<char> mino[3];

    auto empt = std::vector<char>{ '.', '.', '.', '.' };

    REP(i, 3) {
        mino[i].resize(4, 4);
        input >> mino[i];
    }
    debug(mino[0]);
    debug(mino[1]);
    debug(mino[2]);

    FOR(i0, 4) FOR(j0, 4) FOR(i1, 4) FOR(j1, 4) FOR(i2, 4) FOR(j2, 4) {
        REP(d0, 1) REP(d1, 4) REP(d2, 4) {
            lib::grid<char> cp[3];
            std::ranges::copy(mino, std::ranges::begin(cp));

            lib::grid<char> grid(4, 4);

            auto ok = [&]{
                REP(d0) cp[0].rotate();
                REP(d1) cp[1].rotate();
                REP(d2) cp[2].rotate();

                REP(i, 3) {
                    REP(2) {
                        while(cp[i][0] == empt) {
                            REP(j, 1, 4) cp[i][j - 1] = cp[i][j];
                            cp[i][-1] = empt;
                        }
                        cp[i].rotate();
                    }

                    REP(2) cp[i].rotate();
                }

                REP(i, 4) REP(j, 4) {
                    if(cp[0](i, j) == '.') continue;
                    if(!grid.is_valid(i0 + i, j0 + j)) return false;
                    if(grid(i0 + i, j0 + j)) return false;
                    grid(i0 + i, j0 + j) = true;
                }
                REP(i, 4) REP(j, 4) {
                    if(cp[1](i, j) == '.') continue;
                    if(!grid.is_valid(i1 + i, j1 + j)) return false;
                    if(grid(i1 + i, j1 + j)) return false;
                    grid(i1 + i, j1 + j) = true;
                }
                REP(i, 4) REP(j, 4) {
                    if(cp[2](i, j) == '.') continue;
                    if(!grid.is_valid(i2 + i, j2 + j)) return false;
                    if(grid(i2 + i, j2 + j)) return false;
                    grid(i2 + i, j2 + j) = true;
                }
                REP(i, 4) REP(j, 4) {
                    if(!grid(i, j)) return false;
                }
                return true;
            }();

            if(ok) {
                print.yes();
                return;
            }
        }
    }

    print.no();
}
