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

#include "numeric/matrix.hpp"
#include "numeric/modint.hpp"

using mint = lib::modint;

signed main() {
    i64 a, x, m; cin >> a >> x >> m;
    mint::set_mod(m);
    lib::matrix<mint> A = { { a, 1 }, { 0, 1 }};
    print(A.pow(x)(0,1));

    return 0;
}
