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

using mint = lib::modint998244353;

void solve() {
    int n; input >> n;

    lib::vector<std::array<mint, 2>> prob(n + 1), ex(n + 1);
    prob[0] = { 1, 0 };
    ex[0] = { 0, 0 };

    mint n_inv = mint{ n }.inv();

    REP(i, n) {
        mint p = i * n_inv;
        mint h = (1 - p * p).inv();

        mint q = h * (1 - p);

        debug(p, h, q);

        prob[i + 1][0] = prob[i][0] * q * p + prob[i][1] * q;
        prob[i + 1][1] = prob[i][1] * q * p + prob[i][0] * q;

        ex[i + 1][0] = ex[i][0] + prob[i][0] * h * p + prob[i][1] * (h - 1);
        ex[i + 1][1] = ex[i][1] + prob[i][1] * h * p + prob[i][0] * (h - 1);
    }
    debug(prob, ex);

    print(ex[n]);
}
