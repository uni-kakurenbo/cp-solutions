/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i64 n, m; input >> n >> m;

    auto ans = [&](auto&& ans, i64 n, i64 m) -> i64 {
        if(m == 0) return 0;
        if(m == 1) return 1;
        return n * (m / 2) + ans(ans, n, m % 2);
    };

    print(ans(ans, n, m));
}
