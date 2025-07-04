/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "snippet/aliases.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using i32 = int;
using i64 = long;

#include "template/warnings.hpp"
void solve() {
    i32 n; std::cin >> n;
    std::vector<i32> a(n), b(n);
    for(auto& x: a) std::cin >> x;
    for(auto& x: b) std::cin >> x;

    std::vector<std::pair<i32, i32>> ps;

    auto sort = [&](i32 i, i32 j, bool rev = 0) {
        if(i > j) std::swap(i, j);

        if(i == j) return;
        if(i + 1 == j) return;

        std::ranges::sort(a.begin() + i, a.begin() + j);

        if(rev) {
            std::ranges::reverse(a.begin() + i, a.begin() + j);
            std::swap(i, j);
        }

        ps.emplace_back(i, j);
    };

    sort(0, n);

    REP(i, n) {
        auto f = std::ranges::find(a, b[i]) - a.begin();
        if(a[i] < b[i]) {
            sort(i, f + 1, 1);
        }
        else {
            sort(i, f + 1);
        }
    }

    std::cout << ps.size() << "\n";
    for(auto [ l, r ] : ps) {
        char d = 'I';
        if(l > r) {
            std::swap(l, r);
            d = 'D';
        }
        std::cout << l + 1 << " " << r << " " << d << "\n";
    }
}
