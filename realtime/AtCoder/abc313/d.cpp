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
    // input >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

template<class I>
int query(const I first, const I last) {
    print << "? ";
    REP(itr, first, last) print << *itr + 1 << " ";
    std::cout << std::endl;
    int res; input >> res;
    return res;
}

void solve() {
    int n, k; input >> n >> k;

    std::valarray<i64> io(k); std::iota(ALL(io), 0);

    std::valarray<i64> diff(n-1); std::fill(ALL(diff), 0);

    int prev = query(ALL(io));
    int first = prev;
    REP(i, n-k) {
        debug("a");
        io[k-1]++;
        int res = query(ALL(io));
        diff[k+i-1] = res != prev;
        prev = res;
    }
    REP(i, k-1) {
        debug("b");
        io[k-i-2]++;
        int res = query(ALL(io));
        diff[k-i-2] = res != prev;
        prev = res;
    }

    valarray<i64> ans(n);
    REP(i, n-1) ans[i+1] = (ans[i] + diff[i]) % 2;

    if(lib::sum(ans.begin(), ans.begin() + k) % 2 != first) {
        ans *= -1;
        ans += 1;
    }

    print << "! ";
    ITR(x, ans) print << x << " ";
    std::cout << std::endl;
    return;
}
