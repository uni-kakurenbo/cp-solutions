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

#include "multi_vector.hpp"
using namespace Lib;


signed main() {
    int n, m; cin >> n >> m;
    vector<int> a(m); REP(i, m) cin >> a[i], --a[i];

    vector<int> changes_back(n);
    iota(ALL(changes_back), 0);


    REPD(i, m) {
        swap(changes_back[a[i]], changes_back[a[i]+1]);
    }

    debug(changes_back);

    int now = 0;
    REP(i, m) {
        swap(changes_back[a[i]], changes_back[a[i]+1]);
        debug(changes_back);

        int res = changes_back[now];

        debug(now, res);
        print(res + 1);

        if(now == a[i]) ++now;
        else if(now == a[i]+1) --now;
    }

    return 0;
}
