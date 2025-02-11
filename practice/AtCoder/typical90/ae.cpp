/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

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
    i32 n; input >> n;
    valarray<i32> ws(n), bs(n); input >> ws >> bs;

    multi_container<i32, 2> memo(ws.max() + 1, bs.max() + ws.max() * (ws.max() + 1) / 2 + 1, -1);

    auto dfs = [&](auto&& dfs, i32 w, i32 b) -> i32 {
        if(memo[w][b] >= 0) return memo[w][b];

        vector<i32> gs;

        if(w > 0) gs.emplace_back(dfs(dfs, w - 1, b + w));
        if(b > 1) {
            FOR(k, 1, b / 2) {
                gs.emplace_back(dfs(dfs, w, b - k));
            }
        }

        return memo[w][b] = uni::mex(gs);
    };

    i32 grundy = 0;

    ITR(w, b, uni::views::zip(ws, bs)) {
        grundy ^= dfs(dfs, w, b);
    }

    print(grundy == 0 ? "Second" : "First");
}
