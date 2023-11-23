/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/wavelet_matrix.hpp"

void solve() {
    int n; input >> n;
    valarray<i64> p(n); input >> p;
    lib::wavelet_matrix<i64> wm(p);

    // sum_{i < j and P[i] > P[j]} P[i] + P[j]
    i64 ans = 0;

    REP(i, n) {
        ans += wm(0, i).sum_over(p[i]);
        ans += wm(0, i).count_over(p[i]) * p[i];
    }

    print(ans);
}
