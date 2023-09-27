/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

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

#include <atcoder/segtree>
int op(const int a, const int b) { return a + b; }
int e() { return 0; }


void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;

    i64 ans = 0;

    atcoder::segtree<int,op,e> st[10];
    REP(i, m) st[i] = atcoder::segtree<int,op,e>(a.max() + 1);

    REP(i, n) {
        i64 d = a[i] % m;
        ans += st[lib::mod(-d, m)].prod(0, a[i]);
        st[d].set(a[i], st[d].get(a[i]) + 1);
    }

    print(ans);
}
