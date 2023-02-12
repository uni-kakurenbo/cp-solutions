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
    int n, m; cin >> n >> m;
    string s; cin >> s;

    int ans = 0;

    int cnt = 0;
    char nxt = 'I';
    REP(i, m) {
        if(s[i] == nxt) {
            cnt++;
            nxt = nxt == 'I' ? 'O': 'I';
        }
        else {
            cnt = s[i] == 'I';
            nxt = s[i] == 'I' ? 'O': 'I';
        }
        debug(i, s[i], nxt, cnt);
        if((cnt - 1) % 2 == 0 and (cnt - 1) / 2 == n) {
            ans++;
            cnt -= 2;
        }
    }

    print(ans);

    return 0;
}
