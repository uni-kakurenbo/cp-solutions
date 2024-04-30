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

constexpr std::string SNUKE = "snuke";

void solve() {
    i32 h, w; input >> h >> w;
    uni::grid<char> grid(h, w); input >> grid;

    i32 n = std::ranges::ssize(SNUKE);

    REP(i, h) REP(j, w) {
        {
            auto ok = true
            REP(k, n) {

            }
        }
    }
}
