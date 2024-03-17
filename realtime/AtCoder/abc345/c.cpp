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
    string s; input >> s;
    i64 n = s.size();

    i64 ans = lib::nCr(n, 2L);
    debug(ans);

    lib::counter cnt(s);
    debug(cnt);
    ITR(v, c, cnt) {
        ans -= lib::nCr(c, 2L);
    }

    ans += std::ranges::any_of(cnt, [&](auto p) { return p.second > 1; });

    print(ans);
}
