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

#include "template/warnings.hpp"
void solve() {
    i32 n, d; input >> n >> d;
    vector<i64> t(n), l(n); input >> uni::views::zip(t, l);

    FOR(k, 1, d) {
        l += 1;
        print(std::ranges::max(uni::views::zip(t, l) | std::views::transform([&](auto p) { return p.first * p.second; })));
    }
}
