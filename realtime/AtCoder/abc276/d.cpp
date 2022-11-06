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

signed main() {
    int n; cin >> n;
    vector<int> a(n); REP(i, n) cin >> a[i];

    ll ans = INF64;

    int t = accumulate(ALL(a), 0, gcd<int,int>);

    ll cnt = 0;
    REP(j, n) {
        queue<int> que;
        unordered_map<int,int> dists;

        que.push(a[j]), dists[a[j]] = 0;

        while(!que.empty()) {
            int v = que.front(); que.pop();
            for(int d : { 2, 3 }) {
                if(v%d > 0) continue;
                int nv = v/d;
                if(dists.count(nv)) continue;
                dists[nv] = dists[v] + 1;
                que.push(nv);
            }
        }
        debug(dists);
        if(dists.count(t)) cnt += dists[t];
        else goto end;
    }

    ans = cnt;
    end:;

    print(ans == INF64 ? -1 : ans);

    return 0;
}
