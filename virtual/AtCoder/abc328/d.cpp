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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    string s; input >> s;
    int n = std::ranges::ssize(s);

    vector<char> stk;
    REP(i, n) {
        stk.push_back(s[i]);
        const int m = stk.size();
        if(m >= 3UL and string{ stk[m-3], stk[m-2], stk[m-1] } == "ABC") {
            REP(3) stk.pop_back();
        }
        // debug(stk, string{ stk[m-3], stk[m-2], stk[m-1] });
    }
    print(lib::join(stk, ""));
}
