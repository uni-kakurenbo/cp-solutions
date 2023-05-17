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
    int n; cin >> n;
    string s; cin >> s;

    lib::run_length<char> rle(ALL(s));
    debug(rle);

    maximum<int> ans = -1;

    REP(i, rle.size()) {
        if(i > 0) {
            if(rle[i - 1].first == '-') ans <<= rle[i].second;
        }
        if(i < rle.size()-1) {
            if(rle[i + 1].first == '-') ans <<= rle[i].second;
        }
    }

    print(ans);
}
