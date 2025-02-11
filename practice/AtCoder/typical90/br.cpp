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
    i32 n; input >> n;
    vector<i64> x(n), y(n); input >> lib::views::zip(x, y);

    auto xx = lib::sorted(x)[n / 2], yy = lib::sorted(y)[n / 2];

    i64 ans = 0;

    ITR(a, b, lib::views::zip(x, y)) {
        ans += std::abs(xx - a) + std::abs(yy - b);
    }

    print(ans);
}
