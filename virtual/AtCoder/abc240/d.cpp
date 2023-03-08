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

    std::stack<std::pair<int,int>> stk;
    int cnt = 0;
    REP(n) {
        int a; cin >> a;
        if(stk.empty() or stk.top().first != a) {
            stk.emplace(a, 1);
        }
        else {
            stk.top().second++;
        }
        cnt++;
        if(stk.top().first == stk.top().second) {
            cnt -= stk.top().first;
            stk.pop();
        }
        print(cnt);
    }


    return 0;
}
