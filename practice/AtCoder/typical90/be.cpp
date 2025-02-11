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

#include "numeric/matrix.hpp"

using F2 = uni::static_binary_modint_32bit<2>;

void solve() {
    i32 n, m; input >> n >> m;

    uni::matrix<F2> a(m, n);

    REP(i, n) {
        i32 t; input >> t;
        vector<i32> v(t); input >> v;
        ITR(x, v) a(x - 1, i) = 1;
    }

    std::valarray<F2> s(m);
    REP(i, m) {
        char v; input >> v;
        s[i] = v == '1';
    }

    debug(s);

    auto rank = a.solve_linear_equation(s);
    debug(rank);

    if(rank.has_value()) {
        print(MINT<2>.pow(n - *rank));
    }
    else {
        print(0);
        return;
    }
}
