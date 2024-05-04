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
    string s, t; input >> s >> t;
    i32 n = s.ssize();

    vector<i32> ans;

    i32 i = 0;
    ITR(j, v, uni::views::enumerate(t)) {
        if(s[i] == v) {
            ans.emplace_back(j + 1);
            ++i;
        }
    }

    print(ans);
}
