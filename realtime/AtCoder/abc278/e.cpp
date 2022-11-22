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
    int H, W, N, h, w; cin >> H >> W >> N >> h >> w;
    Lib::Grid<int> grid(H, W); grid.read();
    debug(grid);

    std::vector<tuple<int,int,int,int>> covers(N, { INF32, INF32, 0, 0 });

    REP(i, H) REP(j, W) {
        int a = grid(i,j);
        --a;
        chmin(get<0>(covers[a]), i);
        chmin(get<1>(covers[a]), j);
        chmax(get<2>(covers[a]), i);
        chmax(get<3>(covers[a]), j);
    }

    REP(ii, H-h+1){
        REP(ij, W-w+1) {
            int cnt = 0;
            int ji = ii + h, jj = ij + w;
            REP(k, N) {
                if(get<0>(covers[k]) < ii) continue;
                if(get<1>(covers[k]) < ij) continue;
                if(get<2>(covers[k]) >= ji) continue;
                if(get<3>(covers[k]) >= jj) continue;
                ++cnt;
            }
            print << N - cnt << spc;
        }
        print << ln;
    }

    return 0;
}
