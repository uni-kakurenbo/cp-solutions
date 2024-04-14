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

using mint = lib::modint1000000007;

void solve() {
    i128 l, r; input >> l >> r; ++r;

    mint ans = 0;

    REP(d, 19) {
        mint lower = std::clamp(lib::pow(i128{ 10 }, d), l, r);
        mint upper = std::clamp(lib::pow(i128{ 10 }, d + 1), l, r);
        mint cnt = upper * (upper - 1) / 2 - lower * (lower - 1) / 2;
        debug(d, lower, upper, cnt);
        ans += cnt * (d + 1);
    }

    print(ans);
}
