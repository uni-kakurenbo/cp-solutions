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
    i64 a, b, c; cin >> a >> b >> c;
    valarray<string> s(n); input >> s;

    vector<char> ans(n);

    REP(i, n) {
        char res;
        if(s[i] == "AB") {
            if(a > b) res = 'B';
            else if(a < b)  res = 'A';
            else {
                if(i+1 < n and s[i+1] == "AC") res = 'A';
                else res = 'B';
            }
        }
        if(s[i] == "BC") {
            if(b > c) res = 'C';
            else if(b < c)  res = 'B';
            else {
                if(i+1 < n and s[i+1] == "AB") res = 'B';
                else res = 'C';
            }
        }
        if(s[i] == "AC") {
            if(a > c) res = 'C';
            else if(a < c)  res = 'A';
            else {
                if(i+1 < n and s[i+1] == "AB") res = 'A';
                else res = 'C';
            }
        }
        if(res == 'A') {
            ++a;
            if(s[i] == "AB") --b;
            if(s[i] == "AC") --c;
        }
        if(res == 'B') {
            ++b;
            if(s[i] == "AB") --a;
            if(s[i] == "BC") --c;
        }
        if(res == 'C') {
            ++c;
            if(s[i] == "BC") --b;
            if(s[i] == "AC") --a;
        }
        if(a < 0 or b < 0 or c < 0) {
            print("No");
            return;
        }
        ans[i] = res;
    }

    print("Yes");
    debug(ans);
    print(ans);
}
