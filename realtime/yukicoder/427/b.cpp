/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */

#include <bits/stdc++.h>

#include "snippet/aliases.hpp"

void solve();

signed main() {
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        solve();
    }
    return 0;
}



void solve() {
    long n; std::cin >> n;
    std::cout << (n == 1 ? "P" : "K") << "\n";
}
