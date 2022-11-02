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
#include "val_array.hpp"

signed main() {
    int n; ll k; cin >> n >> k;

    ValMatrix<mint> A(n); A.read<int>();
    // debug(A.rows(), A.cols(), A);
    print(A.pow(k).sum());
    // debug(A.rows(), A.cols(), A);

    // ValArray<int> x = {
    //     11, 12, 13, 14
    // };
    // ValArray<int> y = {
    //     11, 12, 13, 14,
    //     21, 22, 23, 24,
    // };
    // debug(x, y);
    // x.assign(ALL(y));
    // y.assign(ALL(x));
    // debug(x, y);

    // auto B = A + A - A + A;

    // B.invert();
    // B.rotate().transpose();

    // B = B + 6 - 4 - 2;
    // B = B * 2 * 4 / 8;

    // debug(std::valarray<bool>(B == A*4/2).min());

    // B = move(A);
    // debug(B);

    // Matrix<int> C = {
    //     { 11, 12, 13, 14 },
    //     { 21, 22, 23, 24 },
    // };
    // debug(C.rows(), C.cols(), C);
    // C.invert();
    // debug(C.rows(), C.cols(), C);
    // C.rotate();
    // debug(C.rows(), C.cols(), C);
    // C.transpose();
    // debug(C.rows(), C.cols(), C);

    // UnfoldedMatrix<int> D = {
    //     { 11, 12, 13, 14 },
    //     { 21, 22, 23, 24 },
    // };
    // debug(D.rows(), D.cols(), D);
    // D.invert();
    // debug(D.rows(), D.cols(), D);
    // D.rotate();
    // debug(D.rows(), D.cols(), D);
    // D.transpose();
    // debug(D.rows(), D.cols(), D);

    return 0;
}
