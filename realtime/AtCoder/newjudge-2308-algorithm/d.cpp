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
    int n0, n1, m; cin >> n0 >> n1 >> m;
    int n = n0 + n1;
    lib::graph<int> G(n); G.read_bidirectionally(m);

    auto a = G.distances_without_cost(0);
    auto b = G.distances_without_cost(n - 1);

    print(*std::ranges::max_element(a | std::views::take(n0)) + *std::ranges::max_element(b | std::views::drop(n0)) + 1);
}
