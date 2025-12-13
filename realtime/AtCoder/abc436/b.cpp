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

    uni::grid<int> g(n, n, -1);

    i32 i = 0, j = n / 2;
    REP(k, n * n) {
        while(g(i, j) >= 0) {
            i = (i + 2) % n;
            j = (j + n - 1) % n;
        }

        debug(k, i, j);
        g(i, j) = k + 1;

        i = (i + n - 1) % n;
        j = (j + 1) % n;
    }

    print(g);
}
