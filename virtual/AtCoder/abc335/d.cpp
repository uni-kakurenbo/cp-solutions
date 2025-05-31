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
    int n; input >> n;
    uni::grid<string> g(n, n);

    i32 m = n / 2;
    g(m, m) = "T";

    i32 len = n;
    i32 i = 0;

    i32 cnt = 0;
    while(true) {
        g(i, i) = std::to_string(++cnt);
        REP(t, 4) {
            debug(i, len);
            if(t == 3) len -= 1;
            REP(j, i + 1, len) {
                if(cnt >= n * n - 2) {
                    g.rotate(3);
                    g(m, m-1) = std::to_string(++cnt);
                    print(g);
                    return;
                }
                g(i, j) = std::to_string(++cnt);
            }
            // debug(g);
            g.rotate(3);
        }
        ++i;
    }
}
