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

mint nCr(ll n, ll r) {
  if (n < r || r < 0) return 0;
  mint a = 1, b = 1;
  REP(i, r) a *= n - i, b *= r - i;
  return a / b;
}

int main() {
  ll N, K;
  cin >> N >> K;
  mint ans;
  if (K >= (N - 1) * (N - 1)) {
    ans = (1 - nCr(N * N - K, N) / nCr(N * N, N * N - K)) * (2 * N + 2);
  } else {
    ans = nCr(K, N) / nCr(N * N, K) * (2 * N + 2);
  }
  print(ans);
}
