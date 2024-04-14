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

    if(n % 2) return;

    vector<string> res;

    REP(x, 1UL << n) {
        int l = 0, r = 0;

        string s;

        bool ok = true;
        REP(i, n) {
            if(lib::bit(x, i)) ++l, s += '(';
            else ++r, s += ')';
            if(l < r) ok = false;
        }
        ok &= r == l;

        if(ok) res.push_back(s);
    }

    res.sort();
    print(res);
}
