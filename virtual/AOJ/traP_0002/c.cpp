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

#include "template/debug.hpp"
// #define debug(...) { ; }

#include "template/warnings.hpp"
void solve() {
    long n, m; cin >> n >> m;
    if(n == 0) exit(0);

    vector<long> a(n), w(m);
    for(auto& x : a) cin >> x;
    for(auto& x : w) cin >> x;

    debug(a, w);

    std::vector<long> vec = { 0 };
    long sz = 1;
    for(auto _ : views::iota(0L, m)) sz *= 3;

    for(unsigned S = 0; S < sz; S++) {
        auto T = S;
        long sum = 0;
        int i = 0;
        while(T > 0) {
            if(T % 3 == 1) sum += w[i];
            if(T % 3 == 2) sum -= w[i];
            T /= 3;
            ++i;
        }
        if(sum > 0) vec.emplace_back(sum);
    }

    {
        std::ranges::sort(vec);
        auto un = std::ranges::unique(vec);
        vec.erase(un.begin(), un.end());
    }
    debug(vec);

    std::map<long, long> cnt;
    long base = 0;

    for(auto x : a) {
        vector<long> r;
        for(auto v : vec) {
            r.push_back(std::abs(x + v));
            r.push_back(std::abs(x - v));
        }

        {
            std::ranges::sort(r);
            auto un = std::ranges::unique(r);
            r.erase(un.begin(), un.end());
        }
        debug(r);

        base += (r[0] == 0);

        for(auto x : r) {
            cnt[x]++;
        }
    }
    debug(base);

    for(auto [ k, v ] : cnt) {
        if(v + base >= n) {
            std::cout << k << "\n";
            return;
        }
    }

    std::cout << "-1\n";
}
