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

// ソートするので個数が大事．

#include "iterable/counter.hpp"

using mint = lib::modint998244353;

signed main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n); input >> a;
    vector<int> cnt(m+1), s(m+2);
    ITR(v, a) cnt[v]++;
    REP(i, 1, m) s[i+1] = s[i] + cnt[i];

    mint ans = 0;

    FOR(i, 1, m) {
        mint pro = 0;
        if(cnt[i] > 0) {
            pro += mint{m}.pow(mint{std::min(cnt[0] - s[i], k)});
        }
        debug(i, pro);
        ans += pro;
    }

    print(ans);

    return 0;
}
