/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i64> a(n); input >> a;
    debug(a);

    std::priority_queue<std::pair<i64, i32>, std::vector<std::pair<i64, i32>>, std::greater<>> que;
    REP(i, n) que.emplace(a[i] * 3, i);
    vector<i64> d(n, 1);
    i64 ans = a.sum();

    REP(n - 2) {
        auto v = que.top(); que.pop();
        ans += v.first;
        ++d[v.second];
        auto r = uni::pow(d[v.second] + 1, 2) - d[v.second] * d[v.second];
        que.emplace(a[v.second] * r, v.second);
    }

    print(ans);
}
