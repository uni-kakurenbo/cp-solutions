/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    // int $ = 0;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
        solve();
    // }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 N; cin >> N;

    vector<int> stk;
    std::string ans(N, '-');

    for (int i=0; i<N; i++) {
        stk.push_back(i);
        if (stk.size() >= 2) {
            std::cout << "? " << stk[-2]+1 << " " << stk[-1]+1 << std::endl;
            char res; cin >> res;
            if (res == '1') {
                ans[stk[-2]] = '(';
                ans[stk[-1]] = ')';
                stk.pop_back(); stk.pop_back();
            }
        }

        debug(stk, ans);
    }

    std::cout << "! " << ans << std::endl;
}
