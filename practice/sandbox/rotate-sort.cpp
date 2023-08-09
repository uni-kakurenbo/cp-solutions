#pragma GCC optimize ("O2")

/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

bool solved = false;
std::unordered_map<std::string,int> dists;
constexpr int N = 12;

constexpr char PDCA[5] = "PDCA";

void solve() {
    std::string s; std::cin >> s;

    if(not solved) {
        queue<std::string> que;

        FOR(i, 1, N) {
            REP(k, 4) {
                std::string pdca;
                REP(j, i) pdca += PDCA[lib::mod(j+k, 4)];
                debug(pdca);
                que.push(pdca), dists[pdca] = 0;
            }
        }

        while(!que.empty()) {
            auto v = que.front(); que.pop();
            FOR(i, 1, v.size()) {
                std::string nv = v;
                REP(j, i) nv[j] = v[lib::mod(j+1, i)];

                if(dists.count(nv)) continue;
                dists[nv] = dists[v] + 1;
                que.push(nv);
            }
        }
        debug(dists.size());
    }

    print(dists.count(s) ? dists[s] : -1);
}
