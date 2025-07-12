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
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/dynamic_sequence.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, m; input >> n >> m;
    vector<i64> a(n); input >> a;
    a.sort();

    uni::priority_queue_rev<std::pair<i64, i32>> pq;
    REP(i, 1, n) {
        pq.emplace(a[i] - a[i - 1], i);
    }

    uni::dynamic_sequence<std::pair<i64, i64>> rs(n);
    REP(i, n) {
        rs[i] = { i, i };
    }

    i64 ans = 0;

    while(m < pq.size() + 1) {
        debug(pq, rs);
        auto [ d, i ] = pq.top(); pq.pop();
        debug(i, d);

        auto l = rs[i - 1].val().first;
        auto r = rs[i].val().second;
        rs.fill(i - 1, i + 1, { l, r });
        ans += d;
    }

    print(ans);
}
