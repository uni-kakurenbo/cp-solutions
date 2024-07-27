/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include <bits/stdc++.h>
// #include "template/standard.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {

        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}




#include "template/warnings.hpp"
void solve() {
    long h, w; std::cin >> h >> w;
    long x, y; std::cin >> y >> x;
    --x, --y;

    long ans = 0;

    for(int i=0; i<h; ++i) {
        if(y != i) ans += h * (h - 1)
    }
}
