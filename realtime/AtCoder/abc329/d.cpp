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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; input >> n >> m;
    valarray<i64> a(m); input >> a; a -= 1;
    valarray<int> cnt(n);

    std::pair<int,int> max = { -1, 0 };
    ITR(v, a) {
        chmax(max, spair<int>{ ++cnt[v], -v });
        print(-max.second + 1);
    }
}
