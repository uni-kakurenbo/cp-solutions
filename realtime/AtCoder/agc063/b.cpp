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

#include "data_structure/wavelet_matrix.hpp"

void solve() {
    int n; cin >> n;
    vector<i64> a(n); input >> a;
    a.reverse();

    lib::wavelet_matrix<i64> wm(ALL(a));
    valarray<i64> nxt(n+1, n);

    REP(i, n) {
        if(a[i] == 1) {
            nxt[i] = i;
            continue;
        }
        int j = wm.select(a[i] - 1, wm(0, i).count(a[i] - 1));
        nxt[i] = j;
    }
    debug(nxt);

    valarray<i64> one(n);
    REP(i, n) one[i] = a[i] == 1;
    lib::accumulation ones(ALL(one));

    REPD(i, n) if(nxt[i] >= 0) nxt[i] = nxt[nxt[i]];

    valarray<i64> ok(n+2, -1);

    i64 ans = 0;
    REPD(i, n) {
        if(a[i] == 1) ok[i] = lib::max(i, ok[i + 1]);
        else {
            ok[i] = lib::max(ok[nxt[i]], ok[nxt[i] + 1]);
        }
        if(ok[i] >= 0 and nxt[i] < n) {
            debug(nxt[i], ok[i]);
            debug(ones[ok[i]+1] - ones[nxt[i]]);
            ans += ones[ok[i]+1] - ones[nxt[i]];
        }
    }
    debug(ok);

    print(ans);
}
