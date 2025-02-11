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

#include "template/warnings.hpp"
void solve() {
    i32 n, m, k; input >> n >> m >> k;
    valarray<i32> a(m), b(m); input >> uni::views::zip(a, b);
    a -= 1, b -= 1;

    uni::graph<> graph(n);
    ITR(u, v, uni::views::zip(a, b)) {
        graph.add_edge(u, v);
    }

    auto deg = graph.in_degrees();

    vector<int> que;
    REP(i, n) {
        if(deg[i] == 0) {
            que.emplace_back(i);
        }
    }

    vector<int> path;
    vector<vector<int>> ans;

    auto dfs = [&](auto&& _dfs) {
        if(path.ssize() == n) {
            ans.push_back(path);

            if(ans.ssize() == k) {
                ITR(row, ans) print(row + 1);
                exit(0);
            }

            return;
        }

        if(que.empty()) {
            print(-1);
            exit(0);
        }

        REPD(i, que.ssize()) {
            const auto v = que[i];
            que.erase(que.begin() + i);

            ITR(e, graph[v]) {
                if(--deg[e] == 0) que.push_back(e);
            }

            path.emplace_back(v);

            _dfs(_dfs);

            path.pop_back();
            ITR(e, graph[v]) {
                if(deg[e]++ == 0) que.pop_back();
            }

            que.insert(que.begin() + i, v);
        }
    };
    dfs(dfs);

    print(-1);
}
