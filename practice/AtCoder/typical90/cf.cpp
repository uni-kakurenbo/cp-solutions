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
    int n; input >> n;
    string s; input >> s;

    lib::inverse rev(s);
    debug(rev);

    i64 ans = 0;

    REP(l, n) {
        if(s[l] == 'o') {
            auto itr = rev['x'].lower_bound(l);
            if(itr == rev['x'].end()) continue;
            ans += n - *itr;
        }
        else {
            auto itr = rev['o'].lower_bound(l);
            if(itr == rev['o'].end()) continue;
            ans += n - *itr;
        }
    }

    print(ans);
}
