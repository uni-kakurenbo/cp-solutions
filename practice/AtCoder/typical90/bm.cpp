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

#include "template/warnings.hpp"
#include "numeric/binomial_coefficient.hpp"
#include "convolution/sum.hpp"

using mint = uni::modint998244353;

void solve() {
    i32 r, g, b, k; input >> r >> g >> b >> k;
    i32 x, y, z; input >> x >> y >> z;

    uni::binomial_coefficient<i32, mint> binom(uni::max(r, g, b));

    vector<mint> u(k + 1), v(k + 1), w(k + 1);
    FOR(i, k) {
        if(k - y <= i && i <= r) u[i] = binom.comb(r, i);
        if(k - z <= i && i <= g) v[i] = binom.comb(g, i);
        if(k - x <= i && i <= b) w[i] = binom.comb(b, i);
    }

    auto d = uni::convolution(u, v);

    mint ans = 0;
    FOR(i, k) ans += d[i] * w[k - i];

    print(ans);
}
