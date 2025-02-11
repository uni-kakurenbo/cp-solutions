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
    string a, b, c; input >> a >> b >> c;

    vector<i32> x = { 0, 1, 2 };
    x.sort([&](auto p, auto q) -> bool {
        if(p == q) return false;
        auto n = p > q;
        if(n) std::swap(p, q);
        if(p == 0 && q == 1) return n ^ (a == "<");
        if(p == 0 && q == 2) return n ^ (b == "<");
        if(p == 1 && q == 2) return n ^ (c == "<");
        assert(false);
    });

    print("ABC"[x[1]]);
}
