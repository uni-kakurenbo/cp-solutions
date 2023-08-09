/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/boundary_seeker.hpp"

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(n), b(m); input >> a >> b;

    auto valid = [&](i64 k) -> bool {
        int cnt_a = std::count_if(ALL(a), [&](i64 v) { return v <= k; });
        int cnt_b = std::count_if(ALL(b), [&](i64 v) { return k <= v;  });
        return cnt_a >= cnt_b;
    };
    lib::boundary_seeker<i64> seeker(valid);
    print(seeker.bound<true>(0, INF64));
}
