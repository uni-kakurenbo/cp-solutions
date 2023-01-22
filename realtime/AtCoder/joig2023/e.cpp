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

#include "grid.hpp"
#include "data_structure/disjoint_set_union.hpp"


const int INF = 1 << 25;


signed main() {
    int h, w; cin >> h >> w;

    lib::grid<int> A(h, w); input >> A;

    lib::dsu ds0(h*w), ds1(h*w);

    vector<set<int>> leaders(w-1);

    REP(k, w) {
        debug(k);
        REP(i, h-1) if(A[i][k] == A[i+1][k]) ds0.merge(i*w + k, (i+1)*w + k);
        if(k < w-1) {
            REP(i, h) {
                if(A[i][k] != A[i][k+1]) continue;
                leaders[k].insert(ds0.leader(i*w + k));
            }

            REP(i, h) if(A[i][k] == A[i][k+1]) ds0.merge(i*w + k, i*w + (k+1));
        }
    }

    REPD(k, w) {
        debug(k);
        REP(i, h-1) if(A[i][k] == A[i+1][k]) ds1.merge(i*w + k, (i+1)*w + k);
        if(k-1 >= 0) {
            REP(i, h) {
                if(A[i][k-1] != A[i][k]) continue;
                leaders[k-1].insert(ds1.leader(i*w + k));
            }

            REP(i, h) if(A[i][k-1] == A[i][k]) ds1.merge(i*w + (k-1), i*w + k);
        }
    }

    int ans = INT_MAX;

    REP(k, w-1) {
        set<int> st;
        ITR(v, leaders[k]) st.insert(ds0.leader(v));
        chmin(ans, ds0.group_count() + ((int)leaders[k].size() - (int)st.size()));
    }

    print(ans);

    return 0;
}
