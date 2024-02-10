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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; input >> n;
    lib::grid<char, string> grid(n, n); input >> grid;

    spair<int> p = { -1, 0 }, q;
    REP(i, n) REP(j, n) {
        if(grid(i, j) != 'P') continue;
        if(p.first == -1) {
            p = { i, j };
        }
        else {
            q = { i, j };
        }
    }
    debug(grid, p, q);

    multi_container<int, 4> dp(n, n, n, n, INF32);

    queue<tuple<int,int,int,int>> que;

    que.emplace(p.first, p.second, q.first, q.second);
    dp(p.first, p.second, q.first, q.second) = 0;

    while(!que.empty()) {
        auto [ i0, j0, i1, j1 ] = que.front(); que.pop();

        REP(d, 4) {
            auto [ ni0, nj0, ni1, nj1 ] = std::make_tuple(i0 + DIRS4[d].first, j0 + DIRS4[d].second, i1 + DIRS4[d].first, j1 + DIRS4[d].second);
            if(!grid.is_valid(ni0, nj0) or grid(ni0, nj0) == '#') std::tie(ni0, nj0) = std::make_tuple(i0, j0);
            if(!grid.is_valid(ni1, nj1) or grid(ni1, nj1) == '#') std::tie(ni1, nj1) = std::make_tuple(i1, j1);
            if(dp(ni0, nj0, ni1, nj1) < INF32) continue;
            dp(ni0, nj0, ni1, nj1) = dp(i0, j0, i1, j1) + 1;
            que.emplace(ni0, nj0, ni1, nj1);
        }
    }

    // debug(dp);

    int ans = INF32;
    REP(i, n) REP(j, n) {
        chmin(ans, dp(i, j, i, j));
    }

    print(lib::to_optional_if_or_over(ans, INF32).value_or(-1));
}
