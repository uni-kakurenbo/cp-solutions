/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    valarray<int> p(n, 0); input(p.begin() + 1, p.end());
    p -= 1;

    valarray<vector<int>> child(n);
    REP(i, n) if(i > 0) child[p[i]].push_back(i);

    map<int,vector<int>> ins;
    valarray<int> in(n), out(n);
    auto dfs = [&](auto&& dfs, int v, int d, int& t) -> void {
        in[v] = t;
        ins[d].push_back(t++);
        ITR(nv, child[v]) dfs(dfs, nv, d+1, t);
        out[v] = t++;
    };
    int t = 0;
    dfs(dfs, 0, 0, t);
    debug(in, out);

    ITRR(d, v, ins) v.sort();

    int q; cin >> q;
    REP(q) {
        // 深さ d, 根が u の部分木に属する
        int u, d; cin >> u >> d; --u;
        print(std::distance(ins[d].lower_bound(in[u]), ins[d].upper_bound(out[u])));
    }
}
