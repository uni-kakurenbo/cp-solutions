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

#include "output.hpp"
#include "template.hpp"

Output _print;
#define print _print
/* #endregion */


#include <atcoder/modint>
using namespace atcoder;
using mint = modint1000000007;

using bit = bitset<46>;

bool operator<(const bit &a, const bit &b) {
  return a.to_ullong() < b.to_ullong();
}

int main() {
    bit a(1100), b(11);
    print(a < b, b < a);
}
