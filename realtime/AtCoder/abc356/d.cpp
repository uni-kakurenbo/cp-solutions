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
#include "numeric/binomial_coefficient.hpp"

using mint = uni::modint998244353;

void solve() {
    u64 n, m; input >> n >> m; ++n;

    mint ans = 0;

    REP(d, 60) {
        if(!uni::bit(m, d)) continue;
        u64 p = uni::div_floor(n, uni::shiftl(1UL, d + 1)) * uni::shiftl(1UL, d);
        i64 q = uni::mod(n, uni::shiftl(1UL, d + 1));
        ans += p + uni::max(q - (i64)uni::shiftl(1UL, d), 0);
        debug(ans);
    }

    print(ans);
}
