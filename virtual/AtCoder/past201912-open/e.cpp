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
    int n, q; cin >> n >> q;

    vector<set<int>> following(n), followed(n);

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int a, b; cin >> a >> b; --a, --b;
            following[a].insert(b);
            followed[b].insert(a);
        }
        if(t == 2) {
            int a; cin >> a; --a;
            ITR(b, followed[a]) {
                following[a].insert(b);
            }
        }
        if(t == 3) {
            int a; cin >> a; --a;
            ITR(b, set(following[a])) ITR(c, following[b]) {
                following[a].insert(c);
                followed[c].insert(a);
            }
        }
        debug(following, followed);
    }

    REP(i, n) {
        string row;
        REP(j, n) {
            row += i!=j and following[i].count(j) ? "Y" : "N";
        }
        print(row);
    }

    return 0;
}
