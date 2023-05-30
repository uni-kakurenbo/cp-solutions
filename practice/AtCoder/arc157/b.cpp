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

#include "iterable/run_length_encoding.hpp"

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;

    int x = std::count(ALL(s), 'X');
    // int y = std::count(ALL(s), 'Y');

    char T;

    if(k <= x) {
        T = 'Y';
    }
    else {
        T = 'X';
        k = n - k;
    }

    lib::run_length<char> rle(s.begin(), s.end());
    vector<int> cand;

    int ans = 0;

    if(rle.size() == 1) {
        if(rle[0].first == T) {
            print(n - 1);
            return;
        }
        else {
            print(std::max(0, k - 1));
            return;
        }
    }

    REP(i, rle.size()) {
        if(rle[i].first == T) {
            ans += rle[i].second - 1;
        }
        else {
            if(i == 0 or i == int(rle.size()) - 1) continue;
            cand.push_back(rle[i].second);
        }
    }

    cand.sort().reverse();
    debug(cand);

    ans += k;

    while(not cand.empty() and cand.back() <= k) {
        k -= cand.back();
        ans++;
        cand.pop_back();
    }

    print(ans);
}
