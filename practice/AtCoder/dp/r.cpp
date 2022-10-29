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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

#include "numeric/matrix.hpp"

signed main() {
    int n; ll k; cin >> n >> k;
    Matrix<mint> A(n); A.read<int>();

    // A = A + 6 - 4 - 2;
    // A = A * 2 * 4 / 8;

    // auto B = A + A - A + A;
    // assert(B == A*4/2);

    A = A.pow(k);

    print(A.sum());

    return 0;
}
