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

using mint = lib::modint1000000007;

void solve() {
    i64 n, k; input >> n >> k;

    mint ans = 1;
    REP(i, lib::min(3, n)) {
        if(i == 0) ans *= k;
        else if(i == 1) ans *= k - 1;
        else ans *= mint{ k - 2 }.pow(n - 2);
    }

    print(ans);
}
