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

void solve() {
    i32 n; input >> n;
    string s; input >> s;

    string ans;

    auto flip = [&](i32 pos) {
        FOR(i, pos) {
            ans += "A";
        }
        REP(i, pos) {
            ans += "B";
        }
    };

    REPD(i, n) {
        if(s[i] == '1') flip(i);
    }

    print(ans.size());
    print(ans);
}
