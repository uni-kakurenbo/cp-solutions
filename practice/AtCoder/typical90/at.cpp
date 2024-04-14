/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i32 n; input >> n;
    lib::multi_container<i32, 2> v(3, n); input >> v;
    std::array<std::array<i32, 46>, 3> cnt{};
    REP(i, 3) ITR(x, v[i]) cnt[i][x % 46]++;
    debug(cnt);

    i64 ans = 0;

    REP(x, 46) REP(y, 46) REP(z, 46) {
        if((x + y + z) % 46 != 0) continue;
        ans += 1L * cnt[0][x] * cnt[1][y] * cnt[2][z];
    }

    print(ans);
}
