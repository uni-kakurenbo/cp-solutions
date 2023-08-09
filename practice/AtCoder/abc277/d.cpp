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

signed main() {
    int n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;

    lib::counter cnt(ALL(a));
    debug(cnt);

    vector<int> visited(n);
    lib::map<ll,ll> memo;

    auto dfs = [&](auto &dfs, int last) -> ll {
        if(memo.count(last)) return memo[last];

        maximum<ll> mx = 0;

        int nxt = lib::mod(last+1, m);
        --cnt[last];

        if(cnt[nxt] > 0) mx <<= dfs(dfs, nxt);
        if(cnt[last] > 0) mx <<= dfs(dfs, last);

        ++cnt[last];

        return memo[last] = last + mx.val();
    };

    maximum<ll> mx = 0;
    REP(i, n) {
        mx <<= dfs(dfs, a[i]);
    }
    print(std::reduce(ALL(a), 0LL) - mx.val());

    return 0;
}
