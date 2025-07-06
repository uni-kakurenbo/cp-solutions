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

#include "include/geometries.hpp"
#include "iterable/accumulation.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n;
    vector<string> _a(n);

    if(n == 0) {
        exit(0);
    }

    input >> _a >> m;
    vector<string> _b(m); input >> _b;

    constexpr i64 BASE = 1'000'000'000;

    std::deque<i64> a(n), b(m);

    auto to_int= [&](auto s) {
        auto itr = s.find('.');

        string t;
        t += s.substr(0, itr - s.begin());
        t += s.substr(itr - s.begin() + 1);
        debug(s, t);
        return std::stoll(t);
    };

    REP(i, n) a[i] = 180 * BASE - to_int(_a[i]);
    REP(i, m) b[i] = 180 * BASE - to_int(_b[i]);

    vector<i64> ans = { n + m + 2 };

    REP(i, n) {
        uni::accumulation cum_a(a);
        // debug(cum_a);
        assert(cum_a.back() == 360 * BASE);
        cum_a.pop_back();

        REP(j, m) {
            uni::accumulation cum_b(b);
            // debug(a, b);
            // debug(cum_a, cum_b);
            assert(cum_b.back() == 360 * BASE);
            cum_b.pop_back();

            vector<i64> vals;
            ITR(x, cum_a) vals.push_back(x);
            ITR(x, cum_b) vals.push_back(x);
            vals.sort().unique();

            // debug(vals);

            ans.push_back(vals.ssize() + 2);

            b.push_back(b.front()), b.pop_front();
        }

        a.push_back(a.front()), a.pop_front();
    }

    ans.sort().unique();
    print(ans);
}
