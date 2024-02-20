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
    int h, w, n; input >> h >> w >> n;
    string t; input >> t;

    lib::grid<char, string> grid(h, w); input >> grid;

    int ans = 0;

    REP(i, h) REP(j, w) {
        if(grid(i, j) == '#') continue;

        int ii = i, jj = j;

        bool ok = true;

        REP(k, n) {
            if(t[k] == 'L') jj--;
            if(t[k] == 'R') jj++;
            if(t[k] == 'U') ii--;
            if(t[k] == 'D') ii++;

            if(not grid.is_valid(ii, jj)) BREAK(ok = false);
            if(grid(ii, jj) == '#') BREAK(ok = false);
        }

        ans += ok;
    }

    print(ans);
}
