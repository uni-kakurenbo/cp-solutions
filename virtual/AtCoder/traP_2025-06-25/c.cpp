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
namespace rng = std::ranges;

void solve();

signed main() {
    // debug(__cplusplus);
    // int $ = 1;
    // std::cin >> $;
    for(;;) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}



// #include "template/debug.hpp"

using i32 = int;
using i64 = long;

constexpr i64 INF = 1L << 62;

// #include "template/warnings.hpp"
void solve() {
    string s; std::cin >> s;
    if(s == "-1") exit(0);

    s = '(' + s + ')';

    i32 n = s.size();
    i32 m = s.size() - rng::count(s, '(') * 2 - 1;
    // debug(n, m);

    vector<i64> vals(n);

    vector<i32> ids(n, -1);

    i32 pool = 0;
    auto id = [&](auto i) {
        if(ids[i] >= 0) return ids[i];
        return ids[i] = pool++;
    };

    vector<vector<i32>> g(m);
    std::stack<i32> stk;

    for(auto i : views::iota(0, n)) {
        auto v = s[i];

        if(v == '(') {
            if(!stk.empty()) {
                auto t = stk.top();
                g[id(t)].push_back(id(i));
                g[id(i)].push_back(id(t));
            }

            stk.push(i);
        }
        else if(v == ')') {
            stk.pop();
        }
        else
        if(std::isdigit(v)) {
            auto t = stk.top();
            g[id(t)].push_back(id(i));
            g[id(i)].push_back(id(t));

            vals[id(i)] = v - '0';
        }
        else {
            auto t = stk.top();

            if(v == '+') vals[id(t)] = -1;
            else vals[id(t)] = -2;
        }
    }

    // debug(vals);

    std::unordered_map<i64, std::pair<i64, i64>> dp;

    auto dfs = [&](auto&& self, i64 v, i64 p) {
        if(vals[v] >= 0) return std::make_pair(vals[v], vals[v]);
        auto key = (p + 1) * m + v;
        if(dp.contains(key)) return dp[key];

        vector<std::pair<i64, i64>> vs;

        for(auto e : g[v]) {
            if(e == p) continue;
            vs.push_back(self(self, e, v));
        }

        std::pair<i64, i64> res = { -INF, INF };

        if(vals[v] == -1) {
            res = { 0, 0 };
            for(auto [ a, b ]: vs) res.first += a, res.second += b;
        }
        else {
            for(auto i : std::views::iota(0uz, vs.size())) {
                auto p = vs[i];
                for(auto j : std::views::iota(1uz, vs.size()) | views::transform([&](auto x) { return (x + i) % vs.size(); })) {
                    p.first -= vs[j].second;
                    p.second -= vs[j].first;
                }
                if(res.first < p.first) res.first = p.first;
                if(res.second > p.second) res.second = p.second;
            }
        }

        return dp[key] = res;
    };

    i64 ans = -INF;

    for(auto i : std::views::iota(0, m)) {
        if(vals[i] >= 0) continue;
        auto v = dfs(dfs, i, -1);
        if(ans < v.first) ans = v.first;
    }

    std::cout << ans << "\n";
}
