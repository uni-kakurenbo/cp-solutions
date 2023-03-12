/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include <atcoder/math>

#include "numeric/prime.hpp"
#include "numeric/prime_table.hpp"
#include "numeric/modint.hpp"
using mint = lib::modint;

signed main() {
    i64 a, x, m; std::cin >> a >> x >> m;
    auto D = lib::divisors(m);
    debug(D);

    if(a%m == 1) {
        print(x % m);
        return 0;
    }

    std::vector<ll> r, v;

    ITR(d, D) {
        if(std::gcd(d, a-1) != 1) continue;
        debug(d, a);
        mint::set_mod(d);
        mint b = a;
        v.push_back(d);
        r.push_back(((b.pow(x) - 1) / (a - 1)).val());
    }

    debug(atcoder::crt(r, v));
    print(atcoder::crt(r, v).first % m);


    return 0;
}
