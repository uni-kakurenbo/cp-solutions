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

#include "data_structure/wavelet_matrix.hpp"

constexpr i32 M = 100'000'000;

void solve() {
    i32 n; input >> n;
    vector<i32> a(n); input >> a;
    uni::wavelet_matrix<i64> wm(a);

    i64 ans = 0;

    REP(i, n) {
        ans += wm(0, i).sum() + 1L * i * a[i] - 1L * M * wm(0, i).count_or_over(M - a[i]);
    }

    print(ans);
}
