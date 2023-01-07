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

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;

    map<int,int> cnt;
    ll sum = 0;
    ITR(v, a) { ++cnt[v], sum += v; }

    int q; cin >> q;
    REP(q) {
        int b, c; cin >> b >> c;
        sum -= 1LL * cnt[b] * b;
        sum += 1LL * cnt[b] * c;
        cnt[c] += cnt[b];
        cnt[b] = 0;
        print(sum);
    }



    return 0;
}
