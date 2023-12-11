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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; input >> n >> m;
    string s; input >> s;

    int p = 0;
    int x = m, y = 0;

    REP(i, n) {
        if(s[i] == '0') {
            x = m, y = p;
        }
        if(s[i] == '1') {
            if(x == 0) {
                if(y == 0) ++p;
                else --y;
            }
            else --x;
        }
        if(s[i] == '2') {
            if(y == 0) ++p;
            else --y;
        }
        debug(x, y);
    }

    print(p);
}
