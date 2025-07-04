/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/small.hpp"
// #include "template/debug.hpp"

#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long;

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 0;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
        solve();
    // }
    return 0;
}

// #include "template/warnings.hpp"
void solve() {
    i64 n, s; std::cin >> n >> s;

    using P = std::pair<i64, i64>;

    std::vector h(n, std::deque<i32>(s));

    for(auto i : std::views::iota(0, n)) {
        for(auto j : std::views::iota(0, s)) {
            std::cin >> h[i][j];
        }
        std::ranges::sort(h[i]);
    }

    std::set<P> st;
    for(auto i : std::views::iota(0, n)) {
        st.emplace(h[i][0], i);
    }

    i64 ans = st.rbegin()->first - st.begin()->first;

    while(true) {
        auto [ _, i ] = *st.begin();
        st.erase(st.begin());
        h[i].pop_front();

        if(h[i].empty()) break;

        st.emplace(h[i][0], i);

        auto v = st.rbegin()->first - st.begin()->first;
        if(ans > v) ans = v;

        // debug(h);
        // debug(st);
    }

    std::cout << ans << "\n";
}
