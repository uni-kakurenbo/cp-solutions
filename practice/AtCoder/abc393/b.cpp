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
    string s; input >> s;
    i32 n = s.size();

    i32 cnt = 0;

    REP(d, n) {
        REP(i, n) {
            if(i + 2 * d >= n) continue;
            if(s[i] == 'A' && s[i + d] == 'B' && s[i + 2 * d] == 'C') {
                cnt++;
            }
        }
    }

    print(cnt);
}
