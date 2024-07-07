/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    string s, t; input >> s >> t;
    s += "..";
    t += "..";

    queue<std::pair<i32, string>> que;
    uni::gp_hash_table<string, i32, std::hash<uni::string>> dists;
    dists.set_default(-1);
    que.emplace(n, s);
    dists[s] = 0;

    while(!que.empty()) {
        auto [p, v] = que.front(); que.pop();
        REP(i, n + 1) {
            if(v[i] == '.') continue;
            if(v[i + 1] == '.') continue;

            auto nv = v;
            nv[p] = v[i];
            nv[p + 1] = v[i + 1];
            nv[i] = nv[i + 1] = '.';

            if(dists[nv] != -1) continue;

            que.emplace(i, nv);
            dists[nv] = dists[v] + 1;
        }
    }
    // debug(dists);

    print(dists[t]);
}
