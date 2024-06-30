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
    string s, t; input >> s >> t;
    i32 n = s.ssize();
    i32 m = t.ssize();

    REP(c, n) {
        REP(w, c + 1, n) {
            // debug(s | uni::views::chunk(w));
            string p;
            ITR(view, s | uni::views::chunk(w)) {
                if((i32)view.size() > c) p += view[c];
            }
            debug(c, w, p);
            if(p == t) {
                print.yes();
                return;
            };
        }
    }

    print.no();
}
