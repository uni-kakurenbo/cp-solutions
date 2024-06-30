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
    vector<i32> a(n); input >> a;
    a -= 1;

    vector<i32> cnt(n);
    vector<i64> size(n);
    auto dfs = [&](auto _dfs, i32 v, i32 t) -> i32 {
        if(cnt[v] == 3) return size[v];
        if(cnt[v] == 2) size[v] = t;
        if(cnt[v] == 1) ++t;
        ++cnt[v];

        auto res = _dfs(_dfs, a[v], t);
        if(cnt[v] == 1) return cnt[v] = 3, size[v] = res + 1;
        else return size[v];
    };
    REP(i, n) if(cnt[i] == 0) dfs(dfs, i, 0);

    debug(size, cnt);
    print(size.sum());
}
