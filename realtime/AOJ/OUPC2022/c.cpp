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
using namespace atcoder;

using mint = modint1000000007;

template<class T> T pow(T x, ll n) {
    assert(0 <= n);
    T r{1};
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

signed main() {
    int x, y; ll t;
    cin >> x >> y >> t;
    complex<mint> top(x, y), rot(1, 1);
    rot = pow(rot, t);

    top = top * rot;

    print(top.real(), top.imag());

    return 0;
}
