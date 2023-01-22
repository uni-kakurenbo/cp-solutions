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

#include "grid.hpp"

signed main() {
    int h, w; cin >> h >> w;

    lib::grid<char,string> grid(h, w); input >> grid;
    debug(grid);

    int ans0 = -1, ans1 = INT_MAX;

    vector<int> cnt_v(w);
    REP(i, h) REP(j, w) cnt_v[j] += grid[i][j] == '#';
    debug(cnt_v);

    REP(row, h) {
        REP(j, w) cnt_v[j] += grid[row][j] == '#' ? -1 : 1;
        int cnt_all = accumulate(ALL(cnt_v), 0);
        debug(cnt_v, cnt_all);

        int max_cnt = -1, rev_col = -1;
        REP(col, w) {
            if(chmax(max_cnt, cnt_v[col])) {
                rev_col = col;
            }
        }
        debug(max_cnt, rev_col);

        cnt_all += h - max_cnt;
        cnt_all -= max_cnt;

        debug(cnt_all, h*w - cnt_all);

        if(chmin(ans1, h*w - cnt_all)) ans0 = cnt_all;

        REP(j, w) cnt_v[j] += grid[row][j] == '#' ? 1 : -1;
    }

    print(ans0, ans1);

    return 0;
}
