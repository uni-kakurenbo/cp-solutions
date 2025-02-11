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

#include "numeric/leveler.hpp"

void solve() {
    i32 n, k; input >> n >> k;

    vector<i32> cnt(n + 1);
    ITR(p, uni::prime_enumerator(n)) {
        FOR(i, p, n, p) cnt[i]++;
    }

    print(cnt.count_if([&](i32 x) { return x >= k; }));
}
