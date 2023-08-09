/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

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

#include "random/xorshift.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n), b(n); input >> a >> b;

    unordered_map<int,u32> hash;
    hash.set_default([]() { return lib::rand(); });

    unordered_set<int> s, t;
    valarray<u32> p(n+1), q(n+1);
    REP(i, n) {
        p[i+1] = p[i], q[i+1] = q[i];
        if(s.insert(a[i]).second) p[i+1] ^= hash[a[i]];
        if(t.insert(b[i]).second) q[i+1] ^= hash[b[i]];
    }
    debug(p, q);

    int r; cin >> r;
    REP(r) {
        int x, y; cin >> x >> y;
        print(p[x] == q[y] ? "Yes" : "No");
    }
}
