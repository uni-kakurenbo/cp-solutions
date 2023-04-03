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

#include "numeric/boundary_seeker.hpp"

i64 solve(i64 n) {
    debug(n);

    auto ok = [&](i64 b, i64 d) {
        auto s = lib::base_n_vector(n, b);
        if((long)s.size() != d) return false;
        debug(b, s);
        return std::count(ALL(s), 0) + std::count(ALL(s), 1) == (long)s.size();
    };

    i64 ans = 1;
    ans += (n >= 3);

    int d = std::log2(n) + 1;

    FOR(i, 3, d) {
        constexpr i64 SUP = 2'000'000'000'000'000'000L;
        lib::boundary_seeker<i64> seeker(
            [&](auto x) { return lib::pow(lib::static_restrictor<i64,0,SUP>{x}, i-1) <= n; }
        );
        i64 b = seeker.bound(2);
        ans += ok(b, i);
    }

    return ans;
}

signed main() {
    int $; cin >> $;
    while($--) {
        i64 n; cin >> n;
        print(solve(n));
    }
}
