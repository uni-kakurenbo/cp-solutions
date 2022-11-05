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

#include <atcoder/dsu>
using namespace atcoder;

#include "grid.hpp"
#include "graph.hpp"

signed main() {
    uint32_t h, w; cin >> h >> w;
    UnfoldedGrid<char,string> S(h, w); S.read();

    ll ans = 0;

    queue<pair<int,int>> que;
    vector<int> dists(h*w, -1);

    REP(si, h) REP(sj, w) {
        if(S(si, sj) == '.') continue;
        if(dists[si*w+sj] >= 0) continue;

        que.emplace(si, sj), dists[si*w+sj] = 0;

        int cnt0 = 1, cnt1 = 0;

        while(!que.empty()) {
            auto [i, j] = que.front(); que.pop();
            ITRM(di, dj, DIRS4) {
                uint32_t ni = i + di, nj = j + dj;
                if(ni >= h or nj >= w) continue;
                if(S(i, j) == S(ni, nj)) continue;
                if(dists[ni*w+nj] >= 0) continue;
                dists[ni*w+nj] = dists[i*w+j] + 1;
                ++(S(ni, nj) == '#' ? cnt0 : cnt1);
                que.emplace(ni, nj);
            }
        }
        ans += 1LL * cnt0 * cnt1;
    }

    print(ans);

    return 0;
}
