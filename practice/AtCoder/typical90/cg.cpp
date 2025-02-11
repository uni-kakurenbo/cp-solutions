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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i64 k; input >> k;
    auto divs = lib::divisors(k);
    i32 n = divs.size();

    i64 ans = 0;

    REP(i, n) REP(j, i, n) {
        i64 a = divs[i], b = divs[j];
        if(k / a < b) continue;
        if(k % (a * b) != 0) continue;
        ans += (b <= k / (a * b));
    }

    print(ans);
}
