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
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w); G.read();

    int i = 0, j = 0;
    lib::set<std::pair<int,int>> st; st.emplace(0, 0);
    while(true) {
        st.emplace(i, j);
        int pi = i, pj = j;
        if(G(pi,pj) == 'U') i--;
        if(G(pi,pj) == 'D') i++;
        if(G(pi,pj) == 'L') j--;
        if(G(pi,pj) == 'R') j++;
        if(i < 0 or i >= h or j < 0 or j >= w) {
            print(pi+1, pj+1);
            return 0;
        }
        if(st.count({ i, j })) {
            print(-1);
            return 0;
        }
    }

    return 0;
}
