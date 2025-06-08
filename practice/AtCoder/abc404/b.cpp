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
    uni::grid<char, string> s(n), t(n); input >> s >> t;

    i32 ans = INF32;

    REP(rot, 4) {
        i32 cnt = 0;
        REP(i, n) REP(j, n) cnt += s(i, j) != t(i, j);
        chmin(ans, cnt + rot);

        s.rotate();
    }

    print(ans);
}
