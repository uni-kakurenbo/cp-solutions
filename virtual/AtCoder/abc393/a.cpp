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
    string s0, s1; input >> s0 >> s1;
    if(s0 == "sick" && s1 == "sick") {
        print(1);
    }
    if(s0 == "sick" && s1 == "fine") {
        print(2);
    }
    if(s0 == "fine" && s1 == "sick") {
        print(3);
    }
    if(s0 == "fine" && s1 == "fine") {
        print(4);
    }
}
