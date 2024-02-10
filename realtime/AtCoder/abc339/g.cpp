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
    valarray<i64> a(n); input >> a;

    lib::wavelet_matrix<i64> wm(a);
    debug(wm);

    i64 q; input >> q;

    i64 v = 0;
    REP(q) {
        i64 a, b, c; input >> a >> b >> c;
        i64 l = a ^ v;
        i64 r = b ^ v;
        i64 x = c ^ v;
        print(v = wm(l - 1, r).sum_or_under(x));
    }
}
