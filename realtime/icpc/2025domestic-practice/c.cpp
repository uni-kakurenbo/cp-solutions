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
    int $ = 0;
    while(true) {
        debug_("Case: #" + std::to_string($++));
        solve();
    }
    return 0;
}

#include "numeric/fast_prime.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, k; input >> n >> k;
    if(n == 0) exit(0);

    auto divs = uni::divisors(n);

    i128 x = 0;

    ITR(div, divs) {
        x += k * div;
    }

    debug(x);

    print.yesno(x % n == 0);
}
