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
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i64> a(n); input >> a;
    uni::grid<i64> dp(n + 1, n + 1, -INF64);

    auto rec = [&](auto&& rec, i32 i, i32 j, i32 t) -> i64 {
        if(dp(i, j) > -INF64) return dp(i, j);
        if(i == j) return 0;

        return dp(i, j) = uni::max(t * rec(rec, i + 1, j, -t) + a[i], t * rec(rec, i, j - 1, -t) + a[j - 1]) * t;
    };

    print(rec(rec, 0, n, 1));
}
