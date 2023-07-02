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

int h, w;

std::string snuke = "snuke";

set<tuple<int,int,int>> visited;
void dfs(const lib::grid<char,string>& G, int i, int j, int c) {
    if(visited.contains({ i, j, c })) return;
    visited.emplace(i, j, c);

    if(G(i, j) != snuke[c]) return;

    if(i == h-1 and j == w-1) {
        print("Yes");
        exit(0);
    };
    debug(i, j);

    ITR(ni, nj, G.vicinities4(i, j)) {
        dfs(G, ni, nj, lib::mod(c + 1, 5));
    }
};

void solve() {
    cin >> h >> w;
    lib::grid<char,string> G(h, w); input >> G;
    dfs(G, 0, 0, 0);
    print("No");
}
