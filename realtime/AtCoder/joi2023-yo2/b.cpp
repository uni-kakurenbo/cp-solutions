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

#include "numeric/boundary_seeker.hpp"
#include "utility/applier.hpp"
using namespace Lib;

signed main() {
    int n; cin >> n;
    vector<ll> a(n), b(n), c(n), d(n);
    input >> a >> b >> c >> d;
    sort(ALL(a)), sort(ALL(b)), sort(ALL(c)), sort(ALL(d));
    debug(a, b, c, d);

    Min<ll> ans(INF32);

    auto solve = [&](auto &v0, auto &v1, auto &v2, auto &v3) {
        REP(i, n) {
            auto validate = [&](ll x) -> bool {
                auto ok = [&](auto &u) -> bool {
                    auto near = lower_bound(ALL(u), v0[i]);
                    if(near == u.end()) return false;
                    return *near - v0[i] <= x;
                };
                return ok(v1) and ok(v2) and ok(v3);
            };
            BoundarySeeker<ll> seeker(validate);
            ans <<= seeker.bound_or<true>(-1, INT32_MAX, INT32_MAX);
        }
    };

    solve(a, b, c, d);
    solve(b, c, d, a);
    solve(c, d, a, b);
    solve(d, a, b, c);

    print(ans);

    return 0;
}
