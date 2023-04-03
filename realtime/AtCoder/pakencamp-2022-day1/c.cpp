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
    string s; cin >> s;
    int n = s.size();

    bool can = true;
    REP(i, n) can &= s[i] == s[n-i-1] or s[i] == '?' or s[n-i-1] == '?';


    lib::modint998244353 ans = can;

    REP(i, (n+1) / 2) {
        if(s[i] == '?' and s[n-i-1] == '?') {
            ans *= 26;
        }
    }

    print(ans);

    return 0;
}
