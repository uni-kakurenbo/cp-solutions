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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "iterable/longest_increasing_subsequence.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i32> a(n); input >> a;


    vector<i32> dp;

    REP(i, n) {
        auto itr = dp.lower_bound(a[i]);
        // auto ind = itr - a.begin();
        if(itr == dp.end()) dp.push_back(a[i]);
        else *itr = a[i];
        debug(dp, a);
    }

    print(dp);
}
