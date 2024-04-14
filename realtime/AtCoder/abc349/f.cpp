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

// 41472, 43008

#include "numeric/subset_superset_transform.hpp"

using mint = lib::modint998244353;

void solve() {
    i64 n, m; input >> n >> m;
    vector<i64> a(n); input >> a;

    auto facts = lib::count_factors(m);
    i32 k = facts.ssize();

    std::vector<i64> cnt(1 << k);
    REP(i, n) {
        if(m % a[i] != 0) continue;

        u64 bit = 0;
        ITR(j, div, lib::views::enumerate(facts)) {
            if(a[i] % lib::pow(div.first, div.second) == 0) bit |= 1UL << j;
        }
        cnt[bit]++;
    }
    debug(cnt);

    lib::subset_transform::zeta(cnt);
    debug(cnt);

    vector<mint> ans(1 << k);
    REP(i, 1 << k) ans[i] = MINT<2>.pow(cnt[i]);
    debug(ans);

    lib::subset_transform::mobius(ans);
    debug(ans);

    print(ans[-1] - (m == 1));
}
