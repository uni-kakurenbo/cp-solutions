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
    lib::grid<char,string> G(h, w, '.');

    int x = 0, y = 0;
    int d = 0;
    REP(n) {
        char& cur = G(x, y);
        if(cur == '.') {
            cur = '#';
            d = lib::mod(d + 1, 4);
        }
        else {
            cur = '.';
            d = lib::mod(d - 1, 4);
        }
        x += DIRS4[d].first;
        y += DIRS4[d].second;
        x += h, y += w;
        x %= h, y %= w;
    }

    print(G);
}
