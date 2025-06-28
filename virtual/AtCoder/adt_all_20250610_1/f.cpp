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

#include "numeric/divisor_multiple_transform.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n; input >> n;

    vector<i32> divs(n, 1);
    uni::divisor_transform::zeta(divs);
    debug(divs);

    i64 ans = 0;

    REP(i, 1, n) {
        ans += divs[i] * divs[n - i];
    }

    print(ans);
}
