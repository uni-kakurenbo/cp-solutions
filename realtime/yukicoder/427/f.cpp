/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */

#include <bits/stdc++.h>

#include "snippet/aliases.hpp"

void solve();

signed main() {
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        solve();
    }
    return 0;
}

void solve() {
    int n, k; std::cin >> n >> k;
    std::vector<std::vector<int>> tree(n);

    for(const int _ : std::views::iota(0, n - 1)) {
        int x, y; std::cin >> x >> y; --x, --y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    std::vector<unsigned> a(n); for(auto& v : a) std::cin >> v;

    unsigned sum = 0;

    auto dfs = [&](auto&& dfs, int v, int p, int d) -> void {
        if(d % 2) sum ^= a[v] % (k + 1);
        for(const auto& nv : tree[v]) {
            if(nv == p) continue;
            dfs(dfs, nv, v, d + 1);
        }
    };
    dfs(dfs, 0, -1, 0);

    std::cout << (sum == 0 ? "P" : "K") << "\n";
}
