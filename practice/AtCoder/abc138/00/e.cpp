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

#include "iterable/inverse.hpp"

signed main() {
    string s, t; cin >> s >> t;

    set st_s(ALL(s));
    ITR(c, t) if(!st_s.count(c)) {
        print(-1);
        return 0;
    }

    Inverse inv_s(ALL(s));

    int ind = -1, cnt = 0;
    ITR(c, t) {
        vector<int>::iterator itr;
        while(true) {
            itr = upper_bound(ALL(inv_s[c]), ind);
            if(itr == inv_s[c].end()) ind = -1, ++cnt;
            else break;
        }
        ind = *itr;
    }
    print(cnt * size(s) + ind + 1);

    return 0;
}
