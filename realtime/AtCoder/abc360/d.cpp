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

#include "data_structure/wavelet_matrix.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, t; input >> n >> t;
    string s; input >> s;
    vector<i32> x(n); input >> x;

    vector<i32> y;
    REP(i, n) if(s[i] == '0') y.push_back(x[i]);
    y.sort();
    debug(y);

    i64 ans = 0;

    REP(i, n) {
        if(s[i] == '0') continue;
        auto l = y.lower_bound(x[i]);
        auto r = y.upper_bound(x[i] + 2 * t);
        debug(i, r - l);
        ans += r - l;
    }

    print(ans);
}
