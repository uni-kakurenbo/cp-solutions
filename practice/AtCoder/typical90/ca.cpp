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
    i32 h, w; input >> h >> w;
    lib::matrix<i32> a(h, w), b(h, w); input >> a >> b;

    i64 cnt = 0;

    REP(i, h - 1) REP(j, w - 1) {
        i32 diff = b(i, j) - a(i, j);
        a(i, j) += diff;
        a(i + 1, j) += diff;
        a(i, j + 1) += diff;
        a(i + 1, j + 1) += diff;
        cnt += std::abs(diff);
    }

    REP(i, h) REP(j, w) {
        if(b(i, j) != a(i, j)) {
            print.no();
            return;
        }
    }

    print.yes();
    print(cnt);
}
