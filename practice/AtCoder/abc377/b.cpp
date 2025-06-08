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
    uni::grid<char, string> g(8); input >> g;
    array<i32, 8> h{}, v{};

    REP(i, 8) REP(j, 8) {
        if(g(i, j) == '#') h[i] = true, v[j] = true;
    }

    i64 ans = 0;

    REP(i, 8) REP(j, 8) {
        ans += h[i] == 0 && v[j] == 0;
    }

    print(ans);
}
