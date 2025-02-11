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
    i32 n = s.size();

    vector<string> x;

    while(s != t) {
        bool found = false;
        REP(i, n) {
            if(s[i] > t[i]) {
                s[i] = t[i];
                found = true;
                break;
            }
        }
        if(!found) {
            REPD(i, n) {
                if(s[i] != t[i]) {
                    s[i] = t[i];
                    break;
                }
            }
        }

        x.push_back(s);
    }

    print(x.size());
    print(x);
}
