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
    debug(s);
    valarray<char> st(26); std::iota(ALL(st), 'a');
    debug(st);

    int q; input >> q;
    REP(q) {
        char a, b; std::cin >> a >> b;
        debug(a, b);
        ITRR(c, st) if(c == a) c = b;
    }
    debug(st);

    string ans;
    ITR(c, s) ans += st[c - 'a'];
    print(ans);
}
