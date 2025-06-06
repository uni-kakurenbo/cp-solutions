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
    i32 r, c; input >> r >> c;
    uni::grid<char, string> a(r, c); input >> a;
    auto b = a;

    REP(i, r) REP(j, c) {
        if(a(i, j) == '#' || a(i, j) == '.') continue;
        const auto v = a(i, j) - '0';

        REP(ii, r) REP(jj, c) {
            if(std::abs(i - ii) + std::abs(j - jj) <= v) {
                b(ii, jj) = '.';
            }
        }
    }

    print(b);
}
