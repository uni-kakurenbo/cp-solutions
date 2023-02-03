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

signed main() {
    string s, t; cin >> s >> t;

    auto can_match = [](char x, char y) -> bool {
        return x == y or x == '?' or y == '?';
    };

    std::vector<int> f(t.size()+1), b(t.size()+1);
    f[0] = b[0] = true;

    REP(i, t.size()) {
        if(can_match(s[i], t[i])) f[i+1] = f[i];
        if(can_match(s[s.size()-i-1], t[t.size()-i-1])) b[i+1] = b[i];
    }
    debug(f, b);

    FOR(i, 0UL, t.size()) {
        print((f[i] and b[t.size()-i] ? "Yes" : "No"));
    }

    return 0;
}
