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
    uni::grid<char, std::string> g(n); input >> g;

    auto can = [&](auto x, auto y, auto d) {
        i32 cnt = 0;

        REP(6) {
            if(x >= n || y >= n || x < 0 || y < 0) return false;
            cnt += g(x, y) == '#';
            x += DIRS8[d].first;
            y += DIRS8[d].second;
        }

        return cnt >= 4;
    };

    REP(i, n) REP(j, n) FOR(d, 1, 4) {
        if(can(i, j, d)) {
            debug(i, j, d);
            print.yes();
            return;
        }
    }

    print.no();
}
