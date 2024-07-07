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

#include "template/warnings.hpp"
void solve() {
    array<i64, 6> w[2]; input >> w[0] >> w[1];

    auto line = [&](i32 a, i32 b, i32 c, i32 d) {
        if(a > b) std::swap(a, b);
        if(c > d) std::swap(c, d);
        return (a < d) && (c < b);
    };

    i32 cnt = 0;
    cnt += line(w[0][0], w[0][3], w[1][0], w[1][3]);
    cnt += line(w[0][1], w[0][4], w[1][1], w[1][4]);
    cnt += line(w[0][2], w[0][5], w[1][2], w[1][5]);

    print.yesno(cnt >= 3);
}
