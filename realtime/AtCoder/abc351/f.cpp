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

void solve() {
    i32 n; input >> n;
    uni::wavelet_matrix<i64> a(({
        vector<i64> v(n); input >> v;
        v;
    }));

    i64 ans = 0;

    REP(i, n) {
        auto span = a(i, n);
        ans += span.sum_over(a[i]) - span.count_over(a[i]) * a[i];
    }

    print(ans);
}
