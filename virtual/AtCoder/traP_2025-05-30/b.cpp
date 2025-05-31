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
    i32 n; input >> n;
    i64 t, a; input >> t >> a;
    vector<i64> h(n); input >> h;

    t *= 1000;
    a *= 1000;

    vector<i64> w(n);
    REP(i, n) {
        w[i] = std::abs(t - h[i] * 6 - a);
    }

    print(std::ranges::min_element(w) - w.begin());
}
