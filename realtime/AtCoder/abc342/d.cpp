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
    int n; input >> n;
    valarray<i64> a(n); input >> a;

    vector<vector<i64>> p(n);
    REP(i, n) {
        ITR(x, c, lib::count_factors(a[i])) if(c % 2) p[i].push_back(x);
    }

    lib::counter cnt(ALL(p));
    debug(cnt, p);

    i64 ans = 0;
    i64 cnt0 = a.count(0);
    ans += 2 * cnt0 * (n - cnt0);
    ans += 2 * lib::nCr<i64>(cnt0, 2);

    cnt[{}] -= cnt0;

    debug(ans, cnt0);

    REP(i, n) if(a[i] != 0) {
        debug(a[i], cnt[p[i]] - 1);
        ans += cnt[p[i]] - 1;
    }

    print(ans / 2);
}
