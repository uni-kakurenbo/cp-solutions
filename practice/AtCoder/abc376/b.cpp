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
    i32 n, q; input >> n >> q;

    i32 l = 0, r = 1;
    i64 ans = 0;

    REP(q) {
        char h; i32 t; input >> h >> t; --t;
        if(h == 'L') {
            debug(l, t, r);
            debug(uni::cyclically_ordered<std::less<>>(l, t, r));
            if(uni::cyclically_ordered<std::less<>>(l, t, r)) {
                ans += uni::mod(t - l, n);
            }
            else {
                ans += uni::mod(l - t, n);
            }
            l = t;
        }
        else {
            debug(l, t, r);
            debug(uni::cyclically_ordered<std::less<>>(l, t, r));
            if(uni::cyclically_ordered(l, t, r)) {
                ans += uni::mod(r - t, n);
            }
            else {
                ans += uni::mod(t - r, n);
            }
            r = t;
        }
    }

    print(ans);
}
