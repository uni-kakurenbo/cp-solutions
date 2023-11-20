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

using mint = lib::modint998244353;

void solve() {
    int n, k; input >> n >> k;
    string s; input >> s;

    lib::counter cnt(s);
    lib::factorial<mint> fact(n);

    auto f = [&](int n, int i, int j) -> mint {
        if(i + j > n) return 0;
        return fact(n) * fact.ifact(i) * fact.ifact(j) * fact.ifact(n - i - j);
    };

    mint ans = 0;

    for(int x=0; 2*x <= k; ++x) {
        for(int p=0; 2*x + p <= k; ++p) {
            for(int q=0; 2*x + p + q <= k; ++q) {
                for(int r=0; 2*x + p + q + r <= k; ++r) {
                    // debug(x, p, q, r);
                    mint cur = 1;
                    cur *= f(cnt['A'], x + p, q);
                    cur *= f(cnt['B'], x + q, r);
                    cur *= f(cnt['C'], x + r, p);
                    if(x != 0) cur *= 2;
                    debug(cur);
                    ans += cur;
                }
            }
        }
    }

    print(ans);
}
