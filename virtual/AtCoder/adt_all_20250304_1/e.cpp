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

#include "template/warnings.hpp"
void solve() {
    i32 h, w; input >> h >> w;
    uni::grid<i64> g(h, w); input >> g;

    i32 ans = 0;

    multiset<i64> st;

    auto dfs = [&](auto&& self, int i, int j) {
        if(i < 0 || j < 0 || i >= h || j >= w) return;
        if(st.contains(g(i, j))) return;
        st.insert(g(i, j));

        if(i == h - 1 and j == w - 1) ans++;

        self(self, i + 1, j);
        self(self, i, j + 1);
        st.remove((g(i, j)));
    };

    dfs(dfs, 0, 0);

    print(ans);
}
