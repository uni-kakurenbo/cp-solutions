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

#include "iterable/accumulation.hpp"

#include <atcoder/convolution>

signed main() {
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<i64> a(n), b(m);
    REP(i, n) a[i] = s[i]-'0';
    REP(i, m) b[i] = t[m-i-1]-'0';
    debug(a, b);

    lib::accumulation<i64> p(ALL(a)), q(ALL(b));
    auto conv = atcoder::convolution(a, b);
    debug(conv);

    i64 ans = INF32;
    REP(i, n-m+1) {
        i64 pro = 0;
        pro += p(i, i+m) + q.back() - 2 * conv[m+i-1];
        chmin(ans, pro);
    }

    print(ans);

    return 0;
}
