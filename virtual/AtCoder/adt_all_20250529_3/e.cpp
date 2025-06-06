/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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
    string s; input >> s;

    uni::inverse inv(ALL(s));
    uni::run_length rle(ALL(s));

    i32 ans = (s.count('/') > 0);

    REP(i, 1, rle.size() - 1) {
        if(rle[i].first != '/' || rle[i].second != 1) continue;
        if(rle[i - 1].first != '1') continue;
        if(rle[i + 1].first != '2') continue;
        auto v = uni::min(rle[i - 1].second, rle[i + 1].second);
        chmax(ans, v * 2 + 1);
    }

    print(ans);
}
