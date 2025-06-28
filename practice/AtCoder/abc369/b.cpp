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
    i32 n; input >> n;
    vector<i64> a(n);
    vector<char> s(n);
    input >> uni::views::zip(a, s);

    i64 l = -1, r = -1;
    i64 ans = 0;

    REP(i, n) {
        debug(l, r, a[i], s[i]);
        if(s[i] == 'L') {
            if(l < 0) {
                l = a[i];
            }
            else {
                ans += std::abs(l - a[i]);
                l = a[i];
            }
        }
        if(s[i] == 'R') {
            if(r < 0) {
                r = a[i];
            }
            else {
                ans += std::abs(r - a[i]);
                r = a[i];
            }
        }
    }

    print(ans);
}
