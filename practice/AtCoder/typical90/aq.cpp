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
    i32 h, w; input >> h >> w;
    i32 si, sj, ti, tj; input >> si >> sj >> ti >> tj; --si, --sj, --ti, --tj;

    lib::grid<char, string> grid(h, w); input >> grid;

    multi_container<i32, 2> dist(h * w, 4, INF32);
    std::priority_queue<tuple<i32, i32, i32>, std::vector<tuple<i32, i32, i32>>, std::greater<tuple<i32, i32, i32>>> que;
    REP(d, 4) {
        dist[grid.id(si, sj)][d] = 0;
        que.emplace(0, grid.id(si, sj), d);
    }

    while(!que.empty()) {
        auto [ t, id, d ] = que.top(); que.pop();
        if(dist[id][d] < t) continue;

        auto [ i, j ] = grid.pos(id);

        REP(nd, 4) {
            i32 ni = i + DIRS4[nd].first, nj = j + DIRS4[nd].second;
            if(!grid.is_valid(ni, nj)) continue;
            if(grid(ni, nj) == '#') continue;
            i32 nt = t + (d != nd);
            i32 nid = grid.id(ni, nj);
            if(dist[nid][nd] <= nt) continue;
            dist[nid][nd] = nt;
            que.emplace(nt, nid, nd);
        }
    }
    debug(dist);

    print(dist[grid.id(ti, tj)].min());
}
