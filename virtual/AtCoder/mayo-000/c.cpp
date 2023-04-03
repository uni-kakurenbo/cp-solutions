/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */


signed main() {
    lib::grid<char,string> G(9); input >> G;
    debug(G);

    auto valid = [&](int i, int j) {
        return i >= 0 and i < 9 and j >= 0 and j < 9 and G(i,j) == '#';
    };

    i64 ans = 0;
    REP(ia, 9) REP(ja, 9) {
        REP(di, -8, 9) REP(dj, -8, 9) {
            if(di == 0 and dj == 0) continue;
            int ib = ia + di, jb = ja + dj;
            int ic = ib - dj, jc = jb + di;
            int id = ic - di, jd = jc - dj;
            if(not(valid(ia, ja) and (valid(ib, jb) and valid(ic, jc) and valid(id, jd)))) continue;
            debug(ia, ja);
            debug(ib, jb);
            debug(ic, jc);
            debug(id, jd);
            ans++;
        }
    }

    debug(ans);
    print(ans / 4);

    return 0;
}
