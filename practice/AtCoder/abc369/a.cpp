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
    array<i32, 2> a; input >> a;


    i32 ans = 0;

    FOR(x, -300, 300) {
        std::array<i32, 3> b = { a[0], a[1], x };
        std::ranges::sort(b);

        ans += (b[2] - b[1] == b[1] - b[0]);
    }

    print(ans);
}
