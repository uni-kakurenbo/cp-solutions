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

signed main() {
    int n, m, q; cin >> n >> m >> q;
    vector<pair<int,int>> p(n); REP(i, n) cin >> p[i].$S >> p[i].$F;
    vector<int> x(m); REP(i, m) cin >> x[i];

    sort(RALL(p));

    LOOP(q) {
        int l, r; cin >> l >> r; --l;
        ll ans = 0;
        vector<int> used(m);
        ITRM(v, w, p) {
            int mi = INF32, ind = -1;
            REP(i, m) {
                if(l <= i and i < r) continue;
                if(used[i]) continue;
                if(x[i] < w) continue;
                if(chmin(mi, x[i])) ind = i;
            }
            if(ind < 0) continue;
            used[ind] = true;
            ans += v;
        }
        print(ans);
    }

    return 0;
}
