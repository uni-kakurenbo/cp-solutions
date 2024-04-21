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

void solve() {
    i64 n, a, x, y; input >> n >> a >> x >> y;

    uni::unordered_map<i64, ld> memo;
    auto dfs = [&](auto&& dfs, i64 n) -> ld {
        if(n == 0) return 0;

        if(memo.contains(n)) return memo[n];

        ld res = std::min(
            dfs(dfs, n / a) + x,
            (dfs(dfs, n / 2) + dfs(dfs, n / 3) + dfs(dfs, n / 4) + dfs(dfs, n / 5) + dfs(dfs, n / 6) + y * 6) / 5
        );

        return memo[n] = res;
    };

    print(dfs(dfs, n));
}
