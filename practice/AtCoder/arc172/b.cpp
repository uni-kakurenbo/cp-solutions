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

using mint = lib::modint998244353;

void solve() {
    i64 n, k, l; input >> n >> k >> l;

    mint ans = 1;

    REP(i, n) {
        if(i < n - k) ans *= lib::max(0, l - i);
        else ans *= lib::max(0, l - n + k);
    }

    print(ans);
}
