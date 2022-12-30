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

namespace atcoder {}
using namespace atcoder;

namespace Lib {}
using namespace Lib;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"

signed main() {
    int n; cin >> n;
    vector<char> a(n); vector<int> b(n);
    input >> b >> a;
    debug(a, b);

    Graph G(n);

    int m; cin >> m;
    REP(m) {
        int x, y; cin >> x >> y; --x, --y;
        G.add_edge_bidirectionally(x, y);
    }

    vector<int> visited(n);
    int ans = 0;

    REP(i, n) {
        if(visited[i]) continue;
        int max_b = -1, vet = -1;
        queue<int> que;
        que.push(i), visited[i] = 1;

        while(!que.empty()) {
            auto v = que.front(); que.pop();
            if(chmax(max_b, b[v])) vet = v;
            for(auto& nv : G[v]) {
                if(visited[nv.to]) continue;
                visited[nv.to] = true;
                que.push(nv.to);
            }
        }

        debug(vet);
        if(a[vet] == 'R') ans += 1;
    }

    print(ans);

    return 0;
}
