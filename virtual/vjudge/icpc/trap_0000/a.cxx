/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/small.hpp"
#include <bits/stdc++.h>
using namespace std;

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 0;

        // debug_("Case: #" + std::to_string($++));
        solve();

    return 0;
}

// #include "template/warnings.hpp"
void solve() {
    int n, x ,y;
    std::cin >> n >> x >> y;
    std::vector<int> a(n);
    long long ans = 0;
    for(auto i : std::views::iota(0, n)) {
        cin >> a[i];
    }
    for(auto i : std::views::iota(0, n)) {
        if(x*a[i] <= y)ans += x*a[i];
        else ans += y;
    }

    std::cout << (ans) << "\n";
}
