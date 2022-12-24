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

#include "utility/applier.hpp"
#include "val_array.hpp"
#include "multi_container.hpp"
#include "grid.hpp"

signed main() {
    int n, x; cin >> n >> x;
    vector<int> a(n); REP(i, n) cin >> a[i];

    UnfoldedGrid<int,ValArray<int>> dp(n+1, 10001, -1);

    {
        string s = to_string(x);
        sort(ALL(s));
        do {
            int k = stoi(s);
            dp(0,k) = 0;
        } while(next_permutation(ALL(s)));
    }

    REP(i, n) {
        REP(j, 10001) {
            if(dp(i,j) < 0) continue;
            if(j >= a[i]) {
                string s = to_string(j-a[i]);
                sort(ALL(s));
                do {
                    int k = stoi(s);
                    chmax(dp(i+1, k), dp(i,j) + 1);
                } while(next_permutation(ALL(s)));
            }
            chmax(dp(i+1, j), dp(i,j));
        }
    }

    print(dp.max());

    return 0;
}
