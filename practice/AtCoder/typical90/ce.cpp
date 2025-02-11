/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

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
    i32 n, m; input >> n >> m;

    valarray<i32> as(m), bs(m); input >> uni::views::zip(as, bs);
    as -= 1, bs -= 1;

    vector<i32> deg(n);
    ITR(a, b, uni::views::zip(as, bs)) {
        ++deg[a];
        ++deg[b];
    }

    i32 k = uni::sqrt_floor(m);

    vector<array<vector<i32>, 2>> graph(n);
    ITR(a, b, uni::views::zip(as, bs)) {
        graph[a][deg[b] >= k].push_back(b);
        graph[b][deg[a] >= k].push_back(a);
    }
    // debug(graph);

    vector<i32> color(n, 1);
    vector<spair<i32>> last(n, { -1, 1 });

    i32 q; input >> q;
    REP(i, q) {
        i32 x, y; input >> x >> y; --x;
        // debug(x, deg[x], k);
        if(deg[x] >= k) {
            print(color[x]);
            color[x] = y;
        }
        else {
            spair<i32> res = last[x];
            ITR(v, uni::views::concat(graph[x][0], graph[x][1])) {
                chmax(res, last[v]);
            }
            print(res.second);
        }

        last[x] = { i, y };
        ITR(v, graph[x][1]) color[v] = y;
    }
}
