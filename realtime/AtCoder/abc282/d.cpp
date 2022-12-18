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

#include "graph.hpp"
#include "atcoder/dsu"

using namespace Lib;
using namespace atcoder;

signed main() {
    int n, m; cin >> n >> m;

    Graph<> G(n);
    dsu uf(n);

    LOOP(m) {
        int u, v; cin >> u >> v; --u, --v;
        G.add_edge_bidirectionally(u, v);
        uf.merge(u, v);
    }

    bool flag = true;

    unordered_map<int,int> checked(n);
    unordered_map<int,unordered_map<int,int>> colors;
    unordered_map<int,int> cnt0s;

    REP(v, n) {
        if(checked[uf.leader(v)]) continue;
        checked[uf.leader(v)] = true;

        auto &color = colors[uf.leader(v)];
        auto &cnt0 = cnt0s[uf.leader(v)];

        queue<int> que;
        color[v] = -1, cnt0 = 1;
        que.push(v);

        while(not que.empty()) {
            int qv = que.front(); que.pop();
            for(auto nv : G[qv]) {
                if(color[nv.to] != 0) {
                    if(color[nv.to] == color[qv]) flag = false;
                    continue;
                }
                color[nv.to] = -1 * color[qv];
                if(color[nv.to] == -1) ++cnt0;
                que.push(nv.to);
            }
        }
    }

    if(not flag) {
        print(0);
        return 0;
    }

    debug(colors, cnt0s);

    ll ans = 0;

    REP(i, n) {
        auto &color = colors[uf.leader(i)];
        int cnt0 = cnt0s[uf.leader(i)], cnt1 = uf.size(i) - cnt0;
        if(color[i] == -1) {
            ans += cnt1 - (int)G[i].size();
        }
        if(color[i] == 1) {
            ans += cnt0 - (int)G[i].size();
        }
        ans += n - uf.size(i);
    }

    debug(ans);
    print(ans / 2);

    return 0;
}
