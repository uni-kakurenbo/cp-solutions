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
    i32 h, w; input >> h >> w;
    i32 i, j; input >> i >> j; --i, --j;
    uni::grid<char, string> grid(h, w); input >> grid;
    string x; input >> x;

    ITR(v, x) {
        auto pi = i, pj = j;
        if(v == 'L') --j;
        if(v == 'R') ++j;
        if(v == 'D') ++i;
        if(v == 'U') --i;
        if(grid.is_valid(i, j) && grid(i, j) == '.') {
            continue;
        }
        i = pi, j = pj;
    }

    print(i + 1, j + 1);
}
