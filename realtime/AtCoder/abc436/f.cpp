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

#include "data_structure/wavelet_matrix.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n; input >> n;
    vector<i64> a(n); input >> a; a -= 1;
    uni::inverse<i64> inv(a);

    uni::wavelet_matrix<i32> wm(a);

    i64 ans = (n + 1) * n / 2;

    REP(b, n) {
        auto i = inv[b][0];
        ans += 1L * wm(0, i).count_under(b) * wm(i, n).count_under(b);
    }

    print(ans);
}
