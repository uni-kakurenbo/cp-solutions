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
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint1000000007;

void solve() {
    int n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;

    if(n == k) {
        print(std::accumulate(ALL(a), mint{1}, std::multiplies<mint>{}));
        return;
    }
    if(std::all_of(ALL(a), [&](i64 x) { return x < 0; })) {
        a.sort();
        if(k % 2) a.reverse();
        print(std::accumulate(a.begin(), a.begin() + k, mint{1}, std::multiplies<mint>{}));
        return;
    }

    valarray<int> ind(n); std::iota(ALL(ind), 0);
    std::sort(ALL(ind), [&](int i, int j) { return std::abs(a[i]) < std::abs(a[j]); });
    ind.reverse();

    mint ans = 1;
    int sign = 1;
    REP(i, k) {
        ans *= a[ind[i]];
        sign *= lib::sign(a[ind[i]]);
    }

    if(sign < 0) {
        i64 rem_neg, rem_pos, add_neg, add_pos;
        rem_neg = add_neg = 1;
        rem_pos = add_pos = -1;
        REPD(i, k) {
            if(rem_neg == 1 and a[ind[i]] < 0) rem_neg = a[ind[i]];
            if(rem_pos == -1 and a[ind[i]] > 0) rem_pos = a[ind[i]];
        }
        REP(i, k, n) {
            if(add_neg == 1 and a[ind[i]] < 0) add_neg = a[ind[i]];
            if(add_pos == -1 and a[ind[i]] >= 0) add_pos = a[ind[i]];
        }
        debug(rem_neg, rem_pos, add_neg, add_pos);
        if(
            (add_neg == 1 or rem_pos == -1) or
            (add_pos >= 0 and rem_neg <= 0 and add_pos * rem_pos >= add_neg * rem_neg)
            ) {
            ans /= rem_neg;
            ans *= add_pos;
        }
        else {
            ans /= rem_pos;
            ans *= add_neg;
        }
    }

    print(ans);
}
