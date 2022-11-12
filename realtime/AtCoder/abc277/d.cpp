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

#include <atcoder/dsu>
using namespace atcoder;

#include "iterable/counter.hpp"
#include "utility/applier.hpp"

signed main() {
    int n, m; cin >> n >> m;
    vector<ll> a(n); REP(i, n) cin >> a[i];

    Lib::Counter<int> cnt(ALL(a));
    debug(cnt);

    vector<int> visited(n);
    map<ll,ll> memo;

    auto dfs = [&](auto &dfs, int last) -> ll {
        if(memo.count(last)) return memo[last];

        Max<ll> mx = 0;

        int nxt = mod(last+1, m);
        --cnt[last];

        if(cnt[nxt] > 0) mx <<= dfs(dfs, nxt);
        if(cnt[last] > 0) mx <<= dfs(dfs, last);

        ++cnt[last];

        return memo[last] = last + mx.val();
    };

    Max<ll> mx = 0;
    REP(i, n) {
        mx <<= dfs(dfs, a[i]);
    }
    print(reduce(ALL(a), 0LL) - mx.val());

    return 0;
}
