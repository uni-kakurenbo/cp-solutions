/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED
#include <bits/stdc++.h>
#include "snippet/aliases.hpp"
#include "snippet/iterations.hpp"
// #include "adaptor/io.hpp"
#include "template/debug.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
    for(auto x : std::views::iota(0, $)) solve();
    // }
    return 0;
}

const std::set<std::array<int, 3>> one = {
    {0, 1, 2},
    {1, 2, 0},
    {2, 0, 1},
};

const std::set<std::array<int, 3>> two = {
    {2, 1, 0},
    {1, 0, 2},
    {0, 2, 1},
};

#include "template/warnings.hpp"
void solve() {
    int n; std::cin >> n;
    auto m = 2 * n + 1;
    std::vector<int> a(m); for(auto& x : a) std::cin >> x;
    debug(m, a);

    std::vector<int> b(m - 2);
    REP(i, 2, m) {
        if(one.contains({a[i - 2], a[i - 1], a[i]})) {
            b[i - 2] = 1;
        }
        else if(two.contains({a[i - 2], a[i - 1], a[i]})) {
            b[i - 2] = 2;
        }
        else {
            b[i - 2] = 0;
        }
    }
    debug(b);

    if(b.size() == 1) {
        std::cout << b[0];
        return;
    }

    std::vector<int> c;

    REP(i, m - 2) {
        if(b[i] == 0) {
            if(i % 2 == 0) {
                std::cout << "0\n";
                return;
            }
        }
        else {
            if(i % 2 != 0) {
                std::cout << "0\n";
                return;
            }
            c.push_back(b[i]);
        }
    }
    debug(c);

    int x = c[0];

    REP(i, 1, c.size()) {
        if(c[i] == x) {
            std::cout << "0\n";
            return;
        }
        else {
            x = c[i];
        }
    }

    std::cout << x << "\n";
}
