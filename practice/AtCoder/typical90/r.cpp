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
    i32 t; input >> t;
    i32 l, x, y; input >> l >> x >> y;
    int q; input >> q;

    REP(q) {
        ld e; input >> e;
        ld py = l * std::cos(2 * M_PI * e / t - M_PI_2) / -2;
        ld pz = (l * std::sin(2 * M_PI * e / t - M_PI_2) + l) / 2;
        debug(e, py, pz);

        ld dy = std::abs(py - y);
        print(std::atan2(pz, std::hypot(dy, x)) * 180 / M_PI);
    }
}
