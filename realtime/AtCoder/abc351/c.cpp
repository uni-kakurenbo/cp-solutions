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
    valarray<i32> a(n); input >> a;

    vector<i32> stk;

    ITR(v, a) {
        stk.push_back(v);

        while(std::ranges::ssize(stk) >= 2 && stk[-1] == stk[-2]) {
            i32 x = stk[-1];
            stk.pop_back();
            stk.pop_back();
            stk.push_back(x + 1);
        }

        debug(stk);
    }

    print(stk.ssize());
}
