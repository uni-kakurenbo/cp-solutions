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

#include "utility/apply.hpp"
#include "multi_vector.hpp"
#include "val_array.hpp"

signed main() {
    int n; cin >> n;
    vector<int> x(n), y(n), z(n);
    REP(i, n) cin >> x[i] >> y[i] >> z[i];

    auto cost = [&](const int from, const int to) {
        return 0LL + abs(x[to] - x[from]) + abs(y[to] - y[from]) + max(0, z[to] - z[from]);
    };

    MultiVector<Min<int>,2,ValArray> dp(1 << n, n, Min<int>{INF32/2});

    dp(0, 0) = 0;
    REP(s, 1 << n) REP(from, n) REP(to, n) {
        dp(s | (1 << to), to) <<= dp(s, from).val() + cost(from, to);
    }

    print(dp((1 << n) - 1, 0));

    return 0;
}
