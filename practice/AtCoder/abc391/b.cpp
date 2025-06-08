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
    i32 n, m; input >> n >> m;
    uni::grid<char, string> s(n), t(m);
    input >> s >> t;

    FOR(si, n - m) FOR(sj, n - m) {
        bool ok = true;
        REP(i, m) REP(j, m) {
            if(t(i, j) != s(si + i, sj + j)) {
                ok = false;
                break;
            }
        }
        if(ok) {
            print(si + 1, sj + 1);
            return;
        }
    }
}
