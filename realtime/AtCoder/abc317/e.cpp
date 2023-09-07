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
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w); input >> G;
    debug(G);

    vector<vector<int>> OB0, OB1;
    spair<int> s, g;

    OB0.resize(w);
    OB1.resize(h);

    constexpr char OBS[] = { 'v', '>', '^', '<' };
    REP(i, h) REP(j, w) REP(d, 2) {
        auto& OB = d == 0 ? OB0 : OB1;
        if(G(i, j) == '.') continue;
        if(G(i, j) == 'S') { s = { i, j }; continue; }
        if(G(i, j) == 'G') { g = { i, j }; continue; }
        OB[d ? i : j].push_back(d ? j : i);
    }
    debug(OB0, OB1);

    auto id = [&](int i, int j) { return i*w + j; };

    valarray<int> memo(h*w, -1);
    auto is_valid = [&](int i, int j) -> bool {
        if(G(i, j) == '>') return false;
        if(G(i, j) == '<') return false;
        if(G(i, j) == '^') return false;
        if(G(i, j) == 'v') return false;
        if(G(i, j) == '#') return false;
        if(memo[id(i, j)] >= 0) return memo[id(i, j)];
        debug(i, j);
        REP(d, 4) {
            auto& OB = d%2 == 0 ? OB0 : OB1;
            vector<int>::iterator itr;
            if(d/2 == 0) {
                itr = OB[d%2 ? i : j].lower_bound(d%2 ? j : i);
                if(itr == OB[d%2 ? i : j].begin()) continue;
                --itr;
            }
            else {
                itr = OB[d%2 ? i : j].upper_bound(d%2 ? j : i);
                if(itr == OB[d%2 ? i : j].end()) continue;
            }
            debug(d, *itr, d%2 ? G(i, *itr) : G(*itr, j), OBS[d]);
            if((d%2 ? G(i, *itr) : G(*itr, j)) == OBS[d]) return (memo[id(i, j)] = false);
        }
        return (memo[id(i, j)] = true);
    };

    // REP(i, h) REP(j, w) debug(i, j, is_valid(i, j));

    queue<int> que;
    valarray<i64> dists(h*w, -1);


    que.push(id(s.first, s.second)), dists[id(s.first, s.second)] = 0;

    while(!que.empty()) {
        auto v = que.front(); que.pop();
        ITR(di, dj, DIRS4) {
            int i = v/w + di, j = v%w + dj;
            if(i < 0 or j < 0 or i >= h  or j >= w) continue;
            if(dists[id(i, j)] >= 0) continue;
            if(not is_valid(i, j)) continue;
            dists[id(i, j)] = dists[v] + 1;
            que.push(id(i, j));
        }
    }
    debug(dists);

    print(dists[id(g.first, g.second)]);
}
