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

#include "numeric/interval_scanner.hpp"

signed main() {
    int n, q; input >> n >> q;
    vector<i64> a(n); input >> a;

    vector<spair<int>> queries(q); input >> queries;
    ITRR(query, queries) query.first--;

    i64 res = 0;
    std::vector<int> cnt(200'001, 0);

    auto expand = [&](int p) {
        if(cnt[a[p]] >= 2) res += 1LL * (cnt[a[p]]) * (cnt[a[p]] - 1) / 2;
        cnt[a[p]]++;
    };
    auto contract = [&](int p) {
        cnt[a[p]]--;
        if(cnt[a[p]] >= 2) res -= 1LL * (cnt[a[p]]) * (cnt[a[p]] - 1) / 2;
    };
    auto evaludate = [&]() -> i64 { return res; };

    auto mo = lib::interval_plannner(expand, contract, evaludate);
    print(mo.scan(ALL(queries)));

    return 0;
}
