/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/bit_vector.hpp"
#include "data_structure/disjoint_sparse_table.hpp"
#include "action/range_max.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    string s; input >> s;

    vector<i64> a(n), b(n + 1);
    REP(i, n) a[i] = s[i] == '1';
    REP(i, n) b[i + 1] = b[i] + (s[i] == '1' ? 1 : -1);

    debug(b);

    uni::disjoint_sparse_table<uni::actions::range_max<i64>> c(ALL(b));

    uni::bit_vector bits(ALL(a));
    debug(bits);
    bits.build();

    i64 ans = INF64;

    REP(l, n) {
        i64 cost = bits.rank1(n);
        debug(l, cost, c(l, n + 1).fold().val(), b[l]);
        cost -= c(l, n + 1).fold().val() - b[l];
        debug(cost);
        chmin(ans, cost);
    }

    print(ans);
}
