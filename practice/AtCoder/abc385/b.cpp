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
    i32 h, w, x, y; input >> h >> w >> x >> y; --x, --y;
    uni::grid<char, string> g(h, w); input >> g;
    string s; input >> s;
    i32 n = s.size();
    uni::set<spair<i32>> st;
    REP(i, n) {
        auto d = DIRECTIONS.index(s[i]);
        auto px = x, py = y;
        x += DIRS4[d].first, y += DIRS4[d].second;
        if(g(x, y) == '#') x = px, y = py;
        if(g(x, y) == '@') st.emplace(x, y);
    }
    print(x + 1, y + 1, st.size());
}
