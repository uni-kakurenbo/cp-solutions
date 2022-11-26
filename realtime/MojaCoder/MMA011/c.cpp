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

#include <atcoder/segtree>
using namespace atcoder;

#include "data_structure/range_addition.hpp"

ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }

signed main() {
    int n, q; cin >> n >> q;
    vector<ll> a(n); REP(i, n) cin >> a[i];

    RangeAddition<ll> data(ALL(a));
    debug(data);

    LOOP(q) {
        int t; cin >> t;
        if(t == 1) {
            int l, r, v; cin >> l >> r >> v; --l;
            data.add(l, r, v);
        }
        if(t == 2) {
            int k; cin >> k; --k;
            print(data.get(k));
        }
        debug(data);
    }

    return 0;
}
