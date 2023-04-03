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
    i64 l, n0, n1; cin >> l >> n0 >> n1;

    vector<std::pair<i64,i64>> p(n0), q(n1);
    input >> p >> q;
    debug(p, q);

    map<i64,i64> num0, num1;

    vector<i64> sep = { 0 }; sep.reserve(n0 + n1);
    {
        i64 sum = 0;
        REP(i, n0) {
            num0[sum] = p[i].first;
            sum += p[i].second;
            sep.push_back(sum);
        }
    }
    {
        i64 sum = 0;
        REP(i, n1) {
            num1[sum] = q[i].first;
            sum += q[i].second;
            sep.push_back(sum);
        }
    }
    debug(num0, num1);

    sort(ALL(sep));
    sep.erase(unique(ALL(sep)), sep.end());
    debug(sep);

    i64 ans = 0;
    REP(i, sep.size()-1) {
        debug(i, sep[i]);
        if(prev(num0.upper_bound(sep[i]))->second == prev(num1.upper_bound(sep[i]))->second) {
            ans += sep[i+1] - sep[i];
        }
    }

    print(ans);

    return 0;
}
