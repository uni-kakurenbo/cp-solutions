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
    i32 n, k; input >> n >> k;
    vector<i32> a(n); input >> a;

    i32 empt = k;
    i32 cnt = 0;

    REP(i, n) {
        i32 v = a[i];
        if(v > empt) {
            cnt += 1;
            empt = k - v;
        }
        else {
            empt -= v;
        }
        debug(v, cnt, empt);
    }

    print(cnt + (empt > 0));
}
