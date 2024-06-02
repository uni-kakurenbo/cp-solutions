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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i64 n, a, b; input >> n >> a >> b;
    debug(n, a, b);
    if(n < a) {
        print.no();
        return;
    }
    i64 w = n - a;
    i64 h = std::min(w, uni::div_ceil<i64>(n, 2));
    debug(w, h, w * h);
    print.yesno(b <= w * h);
}

// 95 91 31
