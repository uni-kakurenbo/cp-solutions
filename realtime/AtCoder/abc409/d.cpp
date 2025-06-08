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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    string s; input >> s;
    uni::inverse inv(s);

    auto t = s;
    REP(i, n - 1) chmax(t[i + 1], t[i]);
    debug(t);

    REP(i, n - 1) {
        if(s[i] <= s[i + 1]) continue;
        auto itr = t.upper_bound(s[i]);
        auto j = itr - t.begin();

        auto v = s;

        v.insert(v.begin() + j, v[i]);
        v.erase(v.begin() + i);
        print(uni::min(s, v));
        return;
    }

    print(s);
}
