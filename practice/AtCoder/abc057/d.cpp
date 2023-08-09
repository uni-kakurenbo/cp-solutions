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

#include "numeric/int128.hpp"

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

void solve() {
    int n, a, b; cin >> n >> a >> b;
    valarray<i64> v(n); input >> v;
    v.sort().reverse();

    i64 sum_a = lib::sum(v.begin(), v.begin() + a);
    print((ld)sum_a / a);

    i64 ans = 0;
    using counter = lib::counter<i64,std::map<i64,cpp_int>>;
    counter cnt(ALL(v));

    FOR(i, a, b) {
        i64 prod = 1;
        i64 sum_i = lib::sum(v.begin(), v.begin() + i);
        debug(i, sum_i);
        if(sum_i * a < sum_a * i) break;
        counter cnt_i(v.begin(), v.begin() + i);
        ITR(x, c, cnt_i) {
            debug(x, cnt[x].convert_to<i128>(), c.convert_to<i128>());
            prod *= lib::nCr(cnt[x], c).convert_to<i128>();
        }
        debug(prod);
        ans += prod;
    }

    print(ans);
}
