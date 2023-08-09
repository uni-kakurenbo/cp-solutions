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

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    set<int> a, b;
    REP(i, n+1) {
        if(s[i] == 'A') a.insert(i);
        else b.insert(i);
    }


    FOR(k, 1, n) {
        bool turn = k % 2; // true: alice, false: bob

        if(turn) {
            if(b.empty()) a.erase(a.begin());
            else b.erase(b.begin());
        }
        else {
            if(a.empty()) b.erase(b.begin());
            else a.erase(a.begin());
        }

        if(a.empty()) print("Bob");
        else if(b.empty()) print("Alice");
        else if(a.min() < b.min()) print("Alice");
        else print("Bob");
    }
}
