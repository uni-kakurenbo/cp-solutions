/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

// #include "template/debug.hpp"
// #include "snippet/aliases.hpp"
// #include <bits/stdc++.h>
// using namespace std;

using i32 = int;
using i64 = long;

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 0;
    while(true) {
        debug_("Case: #" + std::to_string($++));
        solve();
    }
    return 0;
}

#include "structure/grid.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    if(n == 0) exit(0);

    uni::grid<i32> g(n); input >> g;

    uni::grid<i32> h(n);

    REP(i, n) REP(j, n) {
        if((i + j) % 2 == 0) {
            h(i, j) = g(i, j);
        }
        else {
            auto ni = i, nj = j;
            auto m = uni::div_ceil(n, 4) * 2;
            if(i * 2 > n) ni -= m;
            else ni += m;
            if(j * 2 > n) nj -= m;
            else nj += m;
            h(ni, nj) = g(i, j);
            debug(g, h);
        }
    }

    print(h);
}
