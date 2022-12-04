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

#include "numeric/matrix.hpp"

signed main() {
    using Motion = Lib::Matrix<ll>;

    int n; cin >> n;
    std::vector<ll> x(n), y(x);
    REP(i, n) cin >> x[i] >> y[i];

    int m; cin >> m;
    std::vector<Motion> motions(m+1, Motion::Identity(3));
    REP(i, m) {
        int t; cin >> t;
        if(t == 1) {
            motions[i+1] = Motion{ { 0, 1, 0 }, { -1, 0, 0 }, { 0, 0, 1 } } * motions[i];
        }
        if(t == 2) {
            motions[i+1] = Motion{ { 0, -1, 0 }, { 1, 0, 0 }, { 0, 0, 1 } } * motions[i];
        }
        if(t == 3) {
            ll p; cin >> p;
            motions[i+1] = Motion{ { -1, 0, 2*p }, { 0, 1, 0 }, { 0, 0, 1 } } * motions[i];
        }
        if(t == 4) {
            ll p; cin >> p;
            motions[i+1] = Motion{ { 1, 0, 0 }, { 0, -1, 2*p }, { 0, 0, 1 } } * motions[i];
        }
    }
    debug(motions);


    int q; cin >> q;
    LOOP(q) {
        int a, b; cin >> a >> b; --b;
        auto res =  motions[a] * Motion{ { x[b] }, { y[b] }, { 1 } };
        print(res(0, 0), res(1, 0));
    }

    return 0;
}
