/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    valarray<i64> c(n); input >> c; c -= 1;

    valarray<string> a(m);
    REP(i, n) a[c[i]] += s[i];

    ITRR(x, a) {
        x.insert(x.begin(), x.back());
        x.pop_back();
    }

    valarray<string::iterator> itr(m);
    REP(i, m) itr[i] = a[i].begin();

    string t;
    REP(i, n) {
        t += *(itr[c[i]]++);
    }

    print(t);

    valarray<spair<int>> r(n);
    std::ranges::sort(r, std::ranges::greater{}, &spair<int>::second);
    debug(r);
}
