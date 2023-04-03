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

#include "grid.hpp"

signed main() {
    int n; cin >> n;
    vector<i64> a(n); input >> a;
    REP(i, n) a[i] *= 10;

    a.emplace_back();

    vector<i64> p[17] = {};
    REP(i, n) {
        i64 v = a[i];
        REP(d, 17) {
            p[d].push_back(v%10);
            v /= 10;
        }
    }
    REP(d, 17) sort(ALL(p[d]));
    debug(p);

    i64 ans = 0;

    REP(d, 1, 17) {
        std::vector<i64> cnt[10];
        REP(v, 10) cnt[v].assign(10, 0);

        REP(i, n) cnt[p[d][i]][p[d-1][i]]++;
        debug(cnt);

        i64 s = 0, t = 0;
        REP(x, 10) REP(y, 10) REP(z, 10) REP(w, 10) {
            if(x + y + (z + w >= 10) >= 10) {
                // s += cnt[x][z] * cnt[y][w];
            }
            t += cnt[x][z] * cnt[y][w] * ((x + y + (z + w >= 10)) % 10);
        }
        debug(s, t);
        ans += s + t;
    }

    print(ans);

    return 0;
}
