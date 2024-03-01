/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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
    string s; input >> s;
    int n = s.size();

    int ans = n;

    REP(i, 1, n) {
        if(s[i-1] != s[i]) {
            debug(i, n - i);
            chmin(ans, lib::max(i, n - i));
        }
    }

    print(ans);
}
