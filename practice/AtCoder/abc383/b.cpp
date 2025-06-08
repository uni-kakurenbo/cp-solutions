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
    i32 h, w, d; input >> h >> w >> d;
    uni::grid<char, string> g(h, w); input >> g;

    i32 ans = 0;

    REP(i0, h) REP(j0, w) {
        if(g(i0, j0) == '#') continue;
        REP(i1, h) REP(j1, w) {
            if(g(i1, j1) == '#') continue;
            i64 cnt = 0;

            REP(i, h) REP(j, w) {
                if(g(i, j) == '#') continue;

                cnt += std::min(
                    uni::manhattan_distance<i32>({ i, j }, { i0, j0 }),
                    uni::manhattan_distance<i32>({ i, j }, { i1, j1 })
                ) <= d;
            }

            if(chmax(ans, cnt)) debug(i0, j0, i1, j1, cnt);
        }
    }

    print(ans);
}
