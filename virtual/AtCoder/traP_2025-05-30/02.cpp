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
    string s; input >> s;

    if(s.size() != 8) {
        print.no();
        return;
    }

    if(
        'A' <= s[0] && s[0] <= 'Z' &&
        'A' <= s[-1] && s[-1] <= 'Z'
    ) {
        if(s[1] == '0') {
            print.no();
            return;
        }

        REP(i, 1, 5) {
            if(!('0' <= s[i] && s[i] <= '9')) {
                print.no();
                return;
            }
        }
        print.yes();
    }
    else {
        print.no();
    }
}
