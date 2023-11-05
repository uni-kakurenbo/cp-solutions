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
    int n, m; input >> n >> m;
    valarray<i64> a(m), b(m); input >> a >> b;
    a -= 1, b -= 1;

    lib::graph<int> G(n);
    REP(i, m) {
        G.add_edge_bidirectionally(a[i], b[i]);
    }

    vector<int> color(n, -1);   // color[v]：頂点 v の色が黒なら 1, 白なら 0, 未探索なら -1
    string ans = "Yes";
    // 全ての頂点について
    for(int v = 0; v < n; ++v) {
        // 頂点 v がすでに訪問済みであれば、スキップ
        if(color[v] != -1) {continue;}
        // そうでなければ、頂点 v を含む連結成分は未探索
        // 頂点 v の色を白で決め打ちしたうえで、幅優先探索を行う
        queue<int> que; // 探索候補の頂点番号を入れるキュー
        color[v] = 0;
        que.push(v);
        // キューに要素が残っている限り
        while(que.size() > 0) {
            int qv = que.front();
            que.pop();
            // 頂点 qv に隣接している頂点 nv について、
            for(auto nv : G[qv]) {
                // nv がすでに探索済みならば、スキップする
                if(color[nv] != -1) {
                    // 隣り合う頂点どうしが同じ色なら、答えは No
                    if(color[nv] == color[qv]) {ans = "No";}
                    continue;
                }
                // そうでなければ、頂点 nv の色を color[qv] と逆にしたうえで、nv も探索候補に入れる
                color[nv] = 1 - color[qv];
                que.push(nv);
            }
        }
    }

    print(ans);
}
