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
    i32 n, t, p; input >> n >> t >> p;
    valarray<i64> l(n); input >> l;

    i32 cnt = 0;
    while(true) {
        if(l.count_if([&](i32 v) { return v >= t; }) >= p) {
            print(cnt);
            return;
        }
        l += 1;
        ++cnt;
    }
}
