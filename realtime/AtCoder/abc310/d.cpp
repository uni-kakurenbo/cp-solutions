/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint1000000007;

void solve() {
    int n, t, m; cin >> n >> t >> m;

  vector<int> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v; --u, --v;
    graph[u] |= 1 << v;
    graph[v] |= 1 << u;
  }
  vector<mint> ind(1 << n);
  vector<int> ppc(1 << n);
  ind[0] = 1;
  for (int i = 1; i < (1 << n); ++i) {
    int bit = __builtin_ctz(i);
    ind[i] = ind[i ^ (1 << bit)] + ind[(i & ~graph[bit]) ^ (1 << bit)];
    ppc[i] = ppc[i ^ (1 << bit)] + 1;
  }
  debug(ind);
  for (int c = 1; c <= t; ++c) {
    mint ans = 0;
    for(int i = 0; i < (1 << n); ++i) {
      ans += ind[i].pow(c) * ((n - ppc[i]) % 2 ? -1 : 1);
    }
    print(ans);
  }
}
