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

#include <vector>
std::vector<int> Generate(int N, long long S) {
  long long s = S;
  std::vector<int> A(4 * N);
  for (int i = 0; i < 4 * N; ++i) {
    A[i] = i / 4 + 1;
  }
  for (int i = 0; i < 4 * N; ++i) {
    s = (s * 2022) % 998244353;
    if (s % 2 != 0) {
      A[i] = -A[i];
    }
  }
  for (int i = 0; i < 4 * N; ++i) {
    s = (s * 2022) % 998244353;
    int j = s % (i + 1);
    int t = A[j];
    A[j] = A[i];
    A[i] = t;
  }
  return A;
}

signed main() {
    int t; cin >> t;
    LOOP(t) {
        int n, s; cin >> n >> s;
        auto gen = Generate(n, s);

    }
}
