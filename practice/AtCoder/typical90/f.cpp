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
    i32 n, k; input >> n >> k;
    string s; input >> s;

    uni::inverse inv(s);
    debug(inv);

    string t;
    i32 ind = -1;
    REP(i, k) {
        REP(v, 'a', 'z' + 1) {
            auto itr = inv[v].upper_bound(ind);
            if(itr == inv[v].end()) continue;
            if(n - *itr < k - i) continue;
            t += v;
            ind = *itr;
            break;
        }
    }

    print(t);
}
