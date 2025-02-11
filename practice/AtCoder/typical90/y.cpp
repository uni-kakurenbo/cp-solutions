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
    i64 n, b; input >> n >> b;

    auto dfs = [&](auto&& dfs, std::string s, i64 prod) -> i32 {
        // debug(s);
        i64 m = prod + b;
        i32 res = uni::sorted(std::to_string(m)) == s && 1 <= m && m <= n;

        if(s.size() >= 11) {
            return res;
        }

        REP(d, int(s.back() - '0'), 10) {
            res += dfs(dfs, s + char(d + '0'), prod * d);
        }

        return res;
    };

    i32 res = 0;
    REP(d, 10) {
        res += dfs(dfs, std::to_string(d), d);
    }

    print(res);
}
