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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}


#include "template/warnings.hpp"
void solve() {
    using mint = uni::modint998244353;

    i64 h, w, k; input >> h >> w >> k;
    uni::factorial<mint> fact(h + w);


    if(k < h + w - 2) {
        print(0);
        return;
    }

    auto len = w + h - 2;
    auto walls = w * (h - 1) + h * (w - 1);
    auto p = fact.bimom(len, h - 1);

    if(k == h + w - 2) {
        print(p);
        return;
    }

    if(k == h + w - 1) {
        print(p * (walls - len));
        return;
    }

    mint ans = 0;

    mint inv = 1;
    FOR(x, 1, h + w) {
        inv *= INV<2>;
        auto val =
            fact.bimom(h - 2, uni::div_floor<i64>(x - 1, 2)) * fact.bimom(w - 2, uni::div_ceil<i64>(x - 1, 2)) +
            fact.bimom(w - 2, uni::div_ceil<i64>(x - 1, 2)) * fact.bimom(w - 2, uni::div_floor<i64>(x - 1, 2));
        ans += val * inv;
    }

    ans *= (walls - len) * (walls - len - 1) * INV<2>;

    print(ans);
}
