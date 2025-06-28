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
    i32 h, w; input >> h >> w;
    uni::grid<char, string> g(h, w); input >> g;

    i32 minx = h + 1, miny = w + 1, maxx = -1, maxy = -1;

    REP(i, h) REP(j, w) {
        if(g(i, j) == '#') {
            chmin(minx, i);
            chmin(miny, j);
            chmax(maxx, i);
            chmax(maxy, j);
        }
    }

    debug(minx, maxx, miny, maxy);

    FOR(i, minx, maxx) FOR(j, miny, maxy) {
        if(g(i, j) == '.') {
            print.no();
            return;
        }
    }

    print.yes();
}
