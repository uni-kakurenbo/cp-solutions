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
    uni::grid<char, string> G(8, 8); input >> G;

    i32 n = 8;

    uni::vector<i32> h(8), v(8);
    REP(i, n) REP(j, n) {
        if(G(i, j) == '#') {
            h[i]++;
            v[j]++;
        }
    }

    i32 ans = 0;

    REP(i, n) REP(j, n) {
        ans += (h[i] == 0 && v[j] == 0);
    }

    print(ans);
}
