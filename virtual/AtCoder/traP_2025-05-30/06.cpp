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
    i32 n; input >> n;
    string s; input >> s;

    uni::set<spair<i32>> ps;
    ps.emplace(0, 0);

    i32 x = 0, y = 0;
    REP(i, n) {
        i32 dx = 0, dy = 0;
        if(s[i] == 'R') dx = 1;
        if(s[i] == 'L') dx = -1;
        if(s[i] == 'U') dy = 1;
        if(s[i] == 'D') dy = -1;
        x += dx, y += dy;
        debug(x, y);
        if(ps.contains({ x, y })) {
            print.yes();
            return;
        }
        ps.emplace(x, y);
    }

    print.no();
}
