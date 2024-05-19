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
    vector<string> s(n);
    vector<i32> t(n); input >> uni::views::zip(s, t);
    vector<i32> inds(n); std::iota(ALL(inds), 0);
    inds.sort([&](i32 i, i32 j) { return s[i] < s[j]; });

    i64 p = t.sum();

    REP(i, n) {
        if(uni::mod(p, n) == i) {
            print(s[inds[i]]);
        }
    }
}
