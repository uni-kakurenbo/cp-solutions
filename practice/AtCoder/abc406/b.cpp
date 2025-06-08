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
    i64 n, k; input >> n >> k;
    vector<i64> a(n); input >> a;

    i64 m = uni::pow(10L, k);

    i64 now = 1;
    ITR(x, a) {
        auto v = uni::mul_clamp(now, x, -INF64, m);
        if(v < m) now = v;
        else now = 1;
    }

    print(now);
}
