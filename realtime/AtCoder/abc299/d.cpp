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

int query(int i) {
    print('?', i+1); std::cout << std::flush;
    int s; cin >> s;
    return s;
}

void out(int p) {
    print('!', p+1);
}

#include "numeric/boundary_seeker.hpp"

void solve() {
    int n; cin >> n;

    auto ok = [&](int i) {return !query(i); };

    lib::boundary_seeker<int> seeker(ok);
    out(seeker.bound(0, n));
}
