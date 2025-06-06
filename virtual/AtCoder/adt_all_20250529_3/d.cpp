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
    i32 n; i64 t; input >> n >> t;
    vector<i64> c(n), r(n); input >> c >> r;

    if(c.count(t)) {
        auto mx =
        std::ranges::max(
            std::views::iota(0, n) | std::views::filter([&](auto i) {
                return c[i] == t;
            }), [&](auto i, auto j) {
                return r[i] < r[j];
            }
        );

        print(mx + 1);
    }
    else {
        auto mx =
        std::ranges::max(
            std::views::iota(0, n) | std::views::filter([&](auto i) {
                return c[i] == c[0];
            }), [&](auto i, auto j) {
                return r[i] < r[j];
            }
        );

        print(mx + 1);
    }
}
