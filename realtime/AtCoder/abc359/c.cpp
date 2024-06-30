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
    i64 sx, sy, tx, ty; input >> sx >> sy >> tx >> ty;

    i64 ans = 0;
    i64 dd = std::min(std::abs(sx - tx), std::abs(sy - ty));
    if(sx <= tx) sx += dd;
    else sx -= dd;

    if(sy <= ty) sy += dd;
    else sy -= dd;

    ans += dd;

    if((sx + sy) % 2 == 0) sx++;
    if((tx + ty) % 2 == 0) tx++;

    ans += std::abs(sy - ty) + std::abs(sx - tx) / 2;

    print(ans);
}
