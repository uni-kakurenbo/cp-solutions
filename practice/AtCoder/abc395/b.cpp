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
    i32 n; input >> n;

    if(n%2 == 1) {
        uni::grid<char, string> g(n, n, '.');

        REP(i, n) REP(j, n) {
            auto dist = uni::chebyshev_distance<i32>({ i, j }, { n/2, n/2 });
            if(dist % 2 == (n/2)%2) g(i, j) = '#';
        }

        print(g);
    }
    else {
        n /= 2;
        uni::grid<char, string> g(n, n, '.');

        REP(i, n) REP(j, n) {
            auto dist = uni::chebyshev_distance<i32>({ i, j }, { 0, 0 });
            if(dist % 2 != n%2) g(i, j) = '#';
        }

        g.rotate(2);

        uni::grid<char, string> h(2*n, 2*n);
        REP(4) {
            REP(i, n) REP(j, n) h(i, j) = g(i, j);
            h.rotate();
        }

        print(h);
    }
}
