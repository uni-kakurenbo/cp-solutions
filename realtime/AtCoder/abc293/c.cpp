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
/* #endregion */

#include "grid.hpp"
#include "graph.hpp"

signed main() {
    int h, w; cin >> h >> w;
    lib::grid<i32> G(h, w); input >> G;

    i32 ans = 0;

    std::multiset<i64> st;
    auto dfs = [&](auto&& dfs, int i, int j) -> void {
        if(i < 0 or j < 0 or i >= h or j >= w) return;
        if(st.count(G(i, j))) return;
        st.insert(G(i, j));
        if(i == h-1 and j == w-1) ans++;
        dfs(dfs, i+1, j);
        dfs(dfs, i, j+1);
        st.erase(st.find(G(i, j)));
    };
    dfs(dfs, 0, 0);

    print(ans);

    return 0;
}
