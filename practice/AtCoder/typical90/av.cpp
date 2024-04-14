/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

void solve() {
    i32 n, k; input >> n >> k;
    vector<spair<i32>> ab(n); input >> ab;

    priority_queue<spair<i32>> que;
    REP(i, n) que.emplace(ab[i].second, i);

    i64 ans = 0;

    REP(k) {
        auto [ v, i ] = que.top(); que.pop();
        ans += v;

        if(i >= 0) {
            que.emplace(ab[i].first - ab[i].second, -1);
        }
    }

    print(ans);
}
