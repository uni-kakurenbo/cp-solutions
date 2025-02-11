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
    i32 n; input >> n;
    vector<string> s(n); input >> s;

    i32 m = std::ranges::max(s | std::views::transform(std::ranges::size));

    ITRR(x, s) {
        if(x.ssize() >= m) continue;
        x += string(m - x.size(), '*');
    }

    debug(s);

    uni::grid<char, string> t(n, m);
    REP(i, n) REP(j, m) t[i][j] = s[i][j];

    debug(t);

    t.rotate();
    debug(t);

    REP(i, m)  {
        t[i].reverse();
        auto con = std::ranges::distance(t[i] | std::views::take_while([&](auto x) { return x == '*'; }));
        debug(con);
        t[i].reverse();
        print(t[i].substr(0, t[i].size() - con));
    }
}
