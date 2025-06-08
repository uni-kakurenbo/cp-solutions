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
    string t, u; input >> t >> u;
    i32 n = t.size();
    i32 m = u.size();

    FOR(i, n - m) {
        auto s = t.substr(i, m);

        bool ok = true;
        REP(j, m) {
            ok &= s[j] == '?' || s[j] == u[j];
        }
        if(ok) {
            print.yes();
            return;
        }
    }

    print.no();
}
