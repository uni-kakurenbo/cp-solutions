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
    string s; input >> s;

    i32 cnt[2]{};

    ITR(c, s) {
        cnt[(bool)std::isupper(c)]++;
    }

    if(cnt[1] > cnt[0]) {
        print(uni::to_uppwer(s));
    }
    else {
        print(uni::to_lower(s));
    }
}
