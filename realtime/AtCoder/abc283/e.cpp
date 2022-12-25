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
    int h, w; cin >> h >> w;
    vector<vector<bool>> grid(h, vector<bool>(w));
    REP(i, h) REP(j, w) {
        bool b; cin >> b;
        grid[i][j] = b;
    }

    auto solve = [&]() -> int {
        auto _grid = grid;

        auto ex_isolated = [&](int i) -> bool {
            REP(j, _grid[i].size()) {
                int cnt = 0;
                ITR(di, dj, DIRS4) {
                    auto ni = i + di, nj = j + dj;
                    if(ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
                    cnt += _grid[i][j] == _grid[ni][nj];
                }
                if(cnt == 0) return true;
            }
            return false;
        };

        int res = 0, rows = 0, cnt = 0;
        debug(_grid);
        REP(i, h) {
            ++rows;
            if(ex_isolated(i)) {
                if(i != h-1) {
                    _grid[i+1].flip();
                    ++cnt;
                }
                if(ex_isolated(i)) {
                    return h+1;
                }
            }
            else {
                debug(i, rows, cnt);
                res += min(cnt, rows - cnt);
                rows = 0;
                cnt = 0;
            }
        }

        return res;
    };

    int ans = INT32_MAX;;

    chmin(ans, solve());
    reverse(ALL(grid));
    chmin(ans, solve());

    print(ans == h+1 ? -1 : ans);

    return 0;
}
