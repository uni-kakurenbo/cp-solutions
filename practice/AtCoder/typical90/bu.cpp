/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

using mint = uni::modint1000000007;

void solve() {
    i32 n; input >> n;
    valarray<char> c(n); input >> c; c -= 'a';
    uni::graph<i32> tree(n); tree.read_bidirectionally(n - 1);

    vector<array<mint, 3>> dp(n);

    auto dfs = [&](auto&& dfs, i32 v, i32 p) -> void {
        dp[v][2] = dp[v][c[v]] = 1;
        debug(v, dp[v]);

        ITR(nv, tree[v]) {
            if(nv == p) continue;
            dfs(dfs, nv, v);

            dp[v][c[v]] *= (dp[nv][2] + dp[nv][c[v]]);
            dp[v][2] *= dp[nv].sum() + dp[nv][2];
        }

        dp[v][2] -= dp[v][c[v]];
        debug(v, dp[v]);
    };
    dfs(dfs, 0, -1);
    debug(dp);

    print(dp[0][2]);
}
