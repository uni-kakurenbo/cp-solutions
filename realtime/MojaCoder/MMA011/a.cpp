/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
#include <bits/stdc++.h>

#include "template.hpp"
#include "output.hpp"

using namespace std;
Output print;

signed main() {
    int n, q; cin >> n >> q;
    vector<int> a(n); REP(i, n) cin >> a[i];

    LOOP(q) {
        int t; cin >> t;
        if (t == 1) {
            int k, v; cin >> k >> v;
            a[k-1] += v;
        }
        else {
            int k; cin >> k;
            print(a[k-1]);
        }
    }

    return 0;
}
