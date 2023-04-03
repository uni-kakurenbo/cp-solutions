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

#include "hash/sequence_hasher.hpp"

signed main() {
    int n; cin >> n;
    vector<i64> s(n); input >> s;
    vector<i64> t(ALL(s)); copy(ALL(s), back_inserter(t));

    lib::sequence_hasher hash(ALL(t));

    int f = 0;
    REP(i, n) {
        int p = hash.lcp(f, f+n, i, i+n);
        if(p == n) continue;
        if(s[i+p] >= s[f+p]) f = i;
    }

    print(t.begin() + f, t.begin() + f + n);

    return 0;
}
