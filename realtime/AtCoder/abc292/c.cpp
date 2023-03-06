/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

#include "numeric/prime.hpp"

signed main() {
    int n; std::cin >> n;

    i64 ans = 0;

    std::map<int,int> cnt;
    REP(v, 1, n) cnt[v] = lib::divisors(v).size();

    FOR(ab, 1, n-1) {
        int cd = n - ab;
        ans += 1LL * cnt[ab] * cnt[cd];
    }

    print(ans);

    return 0;
}
