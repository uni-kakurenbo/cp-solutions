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
    i32 n; input >>  n;

    uni::grid<char, string> s(uni::pow(3, n), uni::pow(3, n), '.');

    auto dfs = [&](auto _dfs, i32 k, i32 i, i32 j) {
        if(k == 0) {
            s[i][j] ='#';
            return;
        }

        auto v = uni::pow(3, k - 1);
        REP(ii, 0, 3 * v, v) {
            REP(jj, 0, 3 * v, v) {
                if(ii == v && jj == v) continue;
                _dfs(_dfs, k - 1, i + ii, j + jj);
            }
        }
    };
    dfs(dfs, n, 0, 0);

    print(s);
}
