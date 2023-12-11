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

#include "numeric/binomial_coefficient.hpp"

void solve() {
    int n; input >> n;
    valarray<i64> a(n); input >> a;
    valarray<int> p(n, 0); input(std::begin(p) + 1, std::end(p));
    p -= 1;
    debug(a, p);

    valarray<int> d(n);
    REP(i, 1, n) d[i] = d[p[i]] + 1;
    debug(d);

    // using mint = lib::static_modint_64bit<(1L << 19) - 1>;
    // lib::binomial_coefficient<i64, mint> binom(2 * n);

    // mint x = 0;
    // REP(i, 0, n) x += binom.comb(2 * n, d[i]) * a[i];

    // if(x == 0) {
    //     if(a[0] > 0) print('+');
    //     if(a[0] < 0) print('-');
    //     if(a[0] == 0) print('0');
    //     return;
    // }

    lib::map<int, i64> s;
    REP(i, n) s[d[i]] += a[i];

    debug(s | std::views::reverse);

    ITR(v, c, s | std::views::reverse) {
        if(c > 0) {
            print('+');
            return;
        }
        else if(c < 0) {
            print('-');
            return;
        }
    }

    print(0);

    // assert(false);
}
