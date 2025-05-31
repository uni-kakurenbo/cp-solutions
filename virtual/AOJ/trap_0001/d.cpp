/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>

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

#include <atcoder/lazysegtree.hpp>
#include "template/warnings.hpp"

long op(long a, long b) { return a + b; }
long e() { return 0; }
long id() { return 0; }
long comp(long x, long y) { return x + y; }
long map(long f, long x) { return f + x; }

void solve() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;

    atcoder::lazy_segtree<long, op, e, long, map, comp, id> cum(n + 1);

    std::vector<long> a(n), v(n);
    for(int i : std::views::iota(0, n)) {
        std::cin >> a[i];
        v[i] = (s[i] == '(' ? 1 : -1);
    }

    for(int i : std::views::iota(0, n)) {
        cum.apply(i + 1, cum.get(i) + v[i]);
    }

    using P = std::pair<long, long>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> cost;

    long ans = 0;

    for(int i : std::views::iota(0, n)) {
        cost.emplace(a[i], i);
        if(cum.get(i) < 0) {
            ans += cost.top().first;
            cum.apply(cost.top().second, n + 1, 2);
        }
    }

    assert(cum.get(n) == 0);

    std::cout << ans << "\n";
}
