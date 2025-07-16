/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED
#include <bits/stdc++.h>
#include "snippet/aliases.hpp"
#include "snippet/iterations.hpp"
// #include "adaptor/io.hpp"
// #include "template/debug.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 0; std::cin >> $;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
    for(auto x : std::views::iota(0, $)) solve();
    // }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    int n; std::cin >> n; std::cout << 2 * n << "\n";
}
