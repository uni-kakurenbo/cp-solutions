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
    vector<i64> a(n); input >> a;

    i64 base = 0;
    std::set<i64> cut = { 0, 360 };
    for(auto x : a) {
        base += x;
        base %= 360;
        cut.insert(base);
    }

    debug(cut);

    i32 ans = 0;

    auto end = std::prev(cut.end());
    for(auto itr=cut.begin(); itr!=end; ++itr) {
        chmax(ans, *(std::next(itr)) - *itr);
    }

    print(ans);
}
