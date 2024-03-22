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
    mint ex[2]{};

    mint n_inv = mint{ n }.inv();

    REP(i, n) {
        mint p = i * n_inv, q = 1 - p;
        mint a = p + q * q;
        mint b = p * q;
        mint c = q * (q + 1);

        std::tie(ex[0], ex[1]) = std::make_pair(a * ex[0] + b * ex[1] + c, a * ex[1] + b * ex[0] + c);
    }

    print(ex[0], ex[1]);
}
