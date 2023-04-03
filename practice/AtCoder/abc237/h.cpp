/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph/minimum_paph_cover.hpp"

signed main() {
    string s; cin >> s;
    i32 n = s.size();

    vector<string> sub;
    REP(i, n) FOR(j, n) {
        string t = s.substr(i, j);
        string u = t; reverse(ALL(u));
        if(t != u) continue;
        sub.push_back(t);
    }
    sort(ALL(sub)), sub.erase(unique(ALL(sub)), sub.end());
    debug(sub);

    i32 m = sub.size();
    lib::graph G(m);
    REP(i, m) REP(j, m) {
        if(i != j and sub[i].find(sub[j]) != string::npos) {
            G.add_edge(i, j);
        }
    }

    print(G.minimum_paph_cover_size_as_dag());

    return 0;
}
