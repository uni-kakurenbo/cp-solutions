/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    int n; std::cin >> n;
    std::vector<long> v(n);
    for(auto i : std::views::iota(0, n)) {
        std::cin >> v[i];
        v[i] += i;
    }

    std::ranges::sort(v);

    for(auto i : std::views::iota(0, n)) {
        v[i] -= i;
    }

    long ans = 1;

    for(auto x : v) {
        ans *= x;
        ans %= 998244353;
    }

    std::cout << ans << "\n";
}
