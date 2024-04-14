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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i64 n; input >> n;
    i64 d; input >> d;
    i64 d2 = d * 2;

    lib::unfolded_grid<i64> a(n, n); input >> a;

    ITR(v, ((i64[2]){ 0, d })) {
        i64 u = (v + d) % d2;
        debug(u, v);
        i64 cost = 0;
        auto b = a;
        REP(i, n) REP(j, n) {
            b(i, j) = lib::div_round(b(i, j), d2) * d2;

            if((i + j) % 2) {
                if(std::abs(a(i, j) - (b(i, j) - v)) < std::abs(a(i, j) - (b(i, j) + v))) {
                    b(i, j) -= v;
                }
                else {
                    b(i, j) += v;
                }
            }
            else {
                if(std::abs(a(i, j) - (b(i, j) - u)) < std::abs(a(i, j) - (b(i, j) + u))) {
                    b(i, j) -= u;
                }
                else {
                    b(i, j) += u;
                }
            }
            cost += std::abs(a(i, j) - b(i, j));
        }
        debug(v, b);

        if(2 * cost <= n * n * d) {
            print(b);
            return;
        }
    }
}
