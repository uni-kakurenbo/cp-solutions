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
    uni::grid<i32> a(h, w); input >> a;

    i64 ans = 0;

    uni::unordered_set<i64> st;

    uni::grid<i64> dp(h, w, -1);
    auto dfs = [&](auto&& dfs, int i, int j) -> i64 {
        if(i >= h or j >= w) return 0;
        if(dp(i, j) >= 0) return dp(i, j);
        if(st.contains(a(i, j))) return dp(i, j) = 0;

        st.insert(a(i, j));

        i64 res = 0;

        res += dfs(dfs, i+1, j);
        res += dfs(dfs, i, j+1);

        st.remove(a(i, j));

        return dp(i, j) = res;
    };

    dp(h-1, w-1) = 1;
    dfs(dfs, 0, 0);

    print(ans);
}
