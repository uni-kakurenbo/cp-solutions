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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

#include <atcoder/dsu>
using namespace atcoder;

#include "grid.hpp"
#include "utility/applier.hpp"
#include "iterable/compression.hpp"

using namespace Lib;

signed main() {
    int h, w; cin >> h >> w;
    UnfoldedGrid<ll> grid(h, w); grid.read();

    dsu uf(h*w);

    UnfoldedGrid<int> visited(h, w);

    auto bfs = [&](int si, int sj) {
        ll c = grid(si, sj);
        queue<pair<int,int>> que;

        que.emplace(si, sj), visited(si, sj) = true;

        while(!que.empty()) {
            auto [i, j] = que.front(); que.pop();
            ITRM(di, dj, DIRS4) {
                int ni = i + di, nj = j + dj;
                if(ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
                if(grid(ni, nj) != c) continue;
                if(visited(ni, nj)) continue;
                visited(ni, nj) = true;
                uf.merge(si*w+sj, ni*w+nj);
                que.emplace(ni, nj);
            }
        }
    };

    REP(i, h) REP(j, w) bfs(i, j);

    auto groups = uf.groups();

    unordered_map<int,int> id;
    REP(i, groups.size()) {
        ITR(v, groups[i]) {
            id[v] = i;
        }
    }

    Grid<int> can_merge(groups.size(), groups.size());

    REP(i, h) REP(j, w) {
        ITRM(di, dj, DIRS4) {
            int ni = i + di, nj = j + dj;
            if(ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
            can_merge(id[i*w+j], id[ni*w+nj]) = true;
        }
    }

    REP(v, groups.size()) can_merge(v, v) = false;

    debug(groups);
    debug(can_merge);

    Max<int> ans(0);

    REP(i, groups.size()) REP(j, groups.size()) {
        if(not can_merge(i, j)) continue;
        ans <<= uf.size(groups[i][0]) + uf.size(groups[j][0]);
    }

    print(ans);

    return 0;
}
