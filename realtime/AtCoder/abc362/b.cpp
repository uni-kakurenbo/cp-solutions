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

using point = uni::point<ld>;

void solve() {
    uni::triangle<point> t; input >> t;
    auto v = t.angles();
    if(
        uni::compare(std::get<0>(v) * 2, M_PIl) == 0 ||
        uni::compare(std::get<1>(v) * 2, M_PIl) == 0 ||
        uni::compare(std::get<2>(v) * 2, M_PIl) == 0
    ) {
        print.yes();
    }
    else {
        print.no();
    }
}
