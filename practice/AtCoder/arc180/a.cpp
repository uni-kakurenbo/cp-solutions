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
    // std::cin >>  $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = uni::modint1000000007;

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    string s; input >> s;

    mint ans = 1;

    i32 cur = 1;

    REP(i, 1, n) {
        if(s[i-1] != s[i]) {
            cur++;
        }
        else {
            debug((cur + 1) / 2);
            ans *= (cur + 1) / 2;
            cur = 1;
        }
    }
    ans *= (cur + 1) / 2;

    print(ans);
}
