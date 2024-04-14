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
    i32 n; input >> n;
    lib::graph<i32> tree(n); tree.read_bidirectionally(n - 1);

    vector<i32> colors;
    tree.is_bipartite(&colors);
    debug(colors);

    i32 cnt0 = colors.count(-1), cnt1 = colors.count(1);

    vector<i32> res;

    if(cnt0 >= cnt1) {
        REP(i, n) if(colors[i] == -1 && res.ssize() < n / 2) res.push_back(i + 1);
    }
    else {
        REP(i, n) if(colors[i] == 1 && res.ssize() < n / 2) res.push_back(i + 1);
    }

    print(res);
}
