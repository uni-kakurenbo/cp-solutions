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

#include "data_structure/set.hpp"

signed main() {
    int n; cin >> n;

    lib::unordered_set<int> al;
    vector<int> a(n);

    REP(i, n) {
        int v; cin >> v;
        if(al.contains(v)) a[i] = INT_MAX;
        else a[i] = v;
        al.insert(v);
    }

    sort(ALL(a));
    debug(a);

    int cnt = 1;
    for(auto itr = a.begin(); itr != a.end(); ++itr) {
        if(*itr != cnt) {
            if(a.end()  - itr >= 2) {
                a.pop_back();
                a.pop_back();
                a.insert(itr, cnt);
                debug(a);
            }
        }
        ++cnt;
    }

    int ans = 0;
    REP(i, n) {
        if(a[i] == ans+1) {
            ++ans;
        }
        else {
            break;
        }
    }

    cout << ans << ln;

    return 0;
}
