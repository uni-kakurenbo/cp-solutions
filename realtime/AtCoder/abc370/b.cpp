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
    i32 n; input >> n;
    vector<vector<i32>> a(n);
    REP(i, n) {
        a[i].resize(i + 1);
        input >> a[i]; a[i] -= 1;
    }

    uni::grid<i32> b(n, n);
    REP(i, n) FOR(j, i) {
        b[j][i] = b[i][j] = a[i][j];
    }

    debug(a, b);

    i32 cur = 0;
    REP(i, n) cur = b[cur][i];

    print(cur + 1);
}
