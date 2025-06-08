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
    uni::run_length rle(s);

    i64 ans = 0;
    i64 cur = 0;
    ITR(k, v, rle) {
        if(cur % 2 == 0) {
            if(k == 'i') {
                ans += v - 1;
                cur += v - 1;
            }
            else {
                ans += v;
                cur += v;
            }
        }
        else {
            if(k == 'o') {
                ans += v - 1;
                cur += v - 1;
            }
            else {
                ans += v;
                cur += v;
            }
        }
        cur += v;
    }

    print(ans + (cur % 2));
}
