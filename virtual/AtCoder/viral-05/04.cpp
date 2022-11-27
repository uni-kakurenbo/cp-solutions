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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "grid.hpp"

signed main() {
    int h, w, k; cin >> h >> w >> k;
    Lib::Grid<char,string> G(h, w); G.read();

    int ans = 0;
    REP(msk_h, 1 << h) REP(msk_v, 1 << w) {
        int cnt = 0;
        REP(i, h) REP(j, w) {
            if(msk_h & (1 << i)) continue;
            if(msk_v & (1 << j)) continue;
            cnt += G(i, j) == '#';
        }
        ans += cnt == k;
    }
    print(ans);
    return 0;
}
