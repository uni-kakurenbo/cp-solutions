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
    vector<pair<int,int>> S(n), E(n);
    REP(i, n) {
        string a; cin >> a;
        S[i] = { stoi(a.substr(0, 2)), stoi(a.substr(2, 2)) };
        E[i] = { stoi(a.substr(5, 2)), stoi(a.substr(7, 2)) };
        (S[i].second /= 5) *= 5;
        ((E[i].second += 4) /= 5) *= 5;
    }
    debug(S, E);

    vector<int> a(25 * 60);
    REP(i, n) {
        a[S[i].first * 60 +  S[i].second]++;
        a[E[i].first * 60 +  E[i].second]++;
    }

    int ans = 0;
    REP(i, a.size()) {

    }


    return 0;
}
