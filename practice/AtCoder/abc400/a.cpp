/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"
#include <print>

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


#include <tr2/dynamic_bitset>

void solve() {
    std::size_t n; std::cin >> n;
    std::tr2::dynamic_bitset bitset(n);

    for(const auto i : std::views::iota(0uz, n)) {
        bitset.set(i, i % 2);
    }

    std::println("{}", bitset.to_string()); // 10101010......
}
