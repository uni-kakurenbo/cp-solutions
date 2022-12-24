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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

#include "multi_container.hpp"

constexpr int MAX_T = 200000;

signed main() {
    int n; cin >> n;
    map<int,int> a[5];
    LOOP(n) {
        int t, x, v; cin >> t >> x >> v;
        a[x][t] = v;
    }

    Lib::MultiVector<ll,2> dp(MAX_T+1, 5, -1);
    dp(0, 0) = 0;

    ll ans = 0;

    REP(t, MAX_T) {
        REP(i, 5) {
            REP(j, 5) if(abs(i-j) <= 1) chmax(dp(t+1, i), dp(t, j));
            const auto tp = a[i].upper_bound(t);
            if(tp == a[i].end()) continue;
            REP(j, 5) {
                if(dp(t,j) < 0) continue;
                const int dx = abs(i-j), dt = tp->$F - t;
                if(dx <= dt) {
                    chmax(dp(tp->$F, i), dp(t, j) + tp->$S);
                    chmax(ans, dp(tp->$F, i));
                }
            }
        }
    }

    print(ans);

    return 0;
}
