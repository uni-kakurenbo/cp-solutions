/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

void solve() {
    std::string s, t; input >> s >> t;
    s += 'x';
    t = lib::to_lower(t);

    debug(s, t);


    i32 n = s.size();

    print.yesno([&]{
        i32 p = -1;
        REP(x, 3) {
            i32 ii = -1;
            REP(i, p + 1, n) {
                if(s[i] == t[x]) {
                    ii = i;
                    break;
                }
            }
            if(ii == -1) return false;
            debug(ii);
            p = ii;
        }

        return true;
    }());
}
