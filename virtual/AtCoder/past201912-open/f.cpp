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

    vector<pair<string,string>> ws;

    int par = -1;
    string cur;
    REP(i, n) {
        cur += s[i];
        if(isupper(s[i])) {
            par++;
            par %= 2;
        }
        if(par == 1) {
            ws.emplace_back(lib::to_lower(cur), cur);
            cur.clear();
        }
    }

    debug(ws);

    sort(ALL(ws));

    string ans;
    ITR(w, ws) ans += w.second;

    print(ans);

    return 0;
}
