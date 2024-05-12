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

using mint = uni::modint998244353;

void solve() {
    i32 n; input >> n;
    vector<i64> a(n); input >> a;

    mint sum = 0;
    mint ans = 0;

    ITR(i, v, a | uni::views::enumerate) {
        i32 dig = std::to_string(v).size();
        debug(v, dig, sum);
        ans += sum * MINT<10>.pow(dig) + v * i;
        sum += v;
    }
    debug(sum);

    print(ans);
}
