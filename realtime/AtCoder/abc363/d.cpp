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
    i128 n; input >> n;
    i128 l = uni::to_base_n_vector(n, 10).size() - 1;
    l -= l == 0 ? 0 : (1L < n && n < 11L * uni::pow(i128{10}, l - 1));
    // debug(n, l, (1L < n && n < 11L * uni::pow(i128{10}, l - 1)));

    i128 p = uni::pow(i128{10},l );
    debug(p);
    n -= p;
    print(n * uni::pow(i128{10}, l) + uni::from_base_n_string<i128>(uni::reversed(uni::to_base_n_string(n / uni::pow(10L, n >= p), 10)), 10));
}
