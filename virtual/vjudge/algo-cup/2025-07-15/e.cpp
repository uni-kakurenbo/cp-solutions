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

#include "template/warnings.hpp"
void solve() {
    long n, k, t; std::cin >> n >> k >> t;

    auto tt = t % (2 * k);
    debug(tt);

    std::vector<char> as(n);
    std::vector<long> bs(n);
    for(auto& x : as) {
        std::cin >> x;
    }
    for(auto& x : bs) {
        std::cin >> x;
    }

    debug(tt);

    std::vector<long> vvs(n);

    REP(i, n) {
        auto x = as[i];
        auto v = bs[i];

        if(x == 'B') {
            v += tt;
            if(v >= k) v = k - (v - k);
            if(v < 0) v = -v;
        }
        else {
            v -= tt;
            if(v < 0) v = -v;
            if(v >= k) v = k - (v - k);
        }

        vvs[i] = v;
    }

    debug(bs, vvs);

    std::vector<long> order(n); std::iota(ALL(order), 0);
    std::ranges::sort(order, [&](long i, long j) {
        return bs[i] < bs[j];
    });
    std::vector<long> rev(n);
    REP(i, n) {
        rev[order[i]] = i;
    }
    debug(order);

    std::ranges::sort(vvs);
    debug(vvs);

    REP(i, n) {
        std::cout << vvs[rev[i]] << " ";
    }
}
