/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    // int $ = 1;
    // std::cin >> $;
    while(true) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}


#include <bits/stdc++.h>
using namespace std;
#include "template/warnings.hpp"
// #include "template/debug.hpp"

template<class T> vector<T> divisors(T n) {
    vector<T> res;
    for (T i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.emplace_back(i);
            if(i*i < n) res.emplace_back(n/i);
        }
    }
    ranges::sort(res);
    return res;
}
using i32=int;
using i64 = long;
void solve() {
    i64 p; std::cin >> p;
    if(p == 0) exit(0);

    auto div = divisors(p);
    // debug(div);

    auto r = (i64)std::ceil(std::cbrt(p));
    // debug(r);
                                                                                                   
    i32 d = div.size();

    i64 ans = p + 2;

    for(auto i : views::iota(0, d)) {
        auto x = div[i];
        if(x > r + 1) break;
        for(auto j : views::iota(0, d) | views::reverse) {
            auto y = div[j];
            if(y < r - 1) break;

            auto g = std::gcd(x * y, p);
            if(g == x * y && p % (x * y) == 0) {
                auto v = x + y + p / (x * y);
                if(v < ans) ans = v;
            }
        }
    }

    std::cout << ans << "\n";
}
