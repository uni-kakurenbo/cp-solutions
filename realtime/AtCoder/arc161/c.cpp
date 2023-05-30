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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    lib::graph G(n); G.read_bidirectionally(n - 1);
    string s; cin >> s;


    vector<int> leaf;
    REP(i, n) if(G.degree(i) == 1) leaf.push_back(i);

    vector<int> score(ALL(G.degrees()));

    vector<int> res(n, -1);
    queue<int> nxt;

    ITR(v, leaf) {
        int u = G[v][0].to;
        int c = s[v] == 'W';
        if(res[u] >= 0 and res[u] != c) {
            print(-1);
            return;
        }
        if(res[u] < 0) nxt.push(u);
        res[u] = c;
    }

    while(not nxt.empty()) {
        int v = nxt.front(); nxt.pop();
        debug(v, res);
        ITR(e, G[v]) {
            if((s[e.to]  == 'W') != res[v]) score[e.to]--;
            debug(e, score);
            if(score[e.to] == G.degree(e.to) / 2 + 1) {
                ITR(f, G[e.to]) {
                    if(res[f.to] >= 0 and res[f.to] != (s[e.to] == 'W')) {
                        print(-1);
                        return;
                    }
                    if(res[f.to] < 0) nxt.push(f.to);
                    res[f.to] = (s[e.to] == 'W');
                }
            }
            else if(score[e.to] < G.degree(e.to) / 2 + 1) {
                print(-1);
                return;
            }
        }
    }

    REP(v, n) {
        int c = s[v] == 'W';

        int cnt = 0;
        ITR(u, G[v]) {
            cnt += (res[u.to] == 'W') != c;
        }

        if(cnt > G.degree(v)) {
            print(-1);
            return;
        }

        ITR(u, G[v]) {
            if(res[u.to] < 0) {
                res[u.to] = c;
            }
        }
    }

    std::replace(ALL(res), -1, 0);

    debug(res);

    REP(i, n) print << "BW"[res[i]];
    print();
}
