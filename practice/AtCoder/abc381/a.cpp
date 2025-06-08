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
    uni::run_length rle(s);
    print.yesno(
        (
            rle.size() == 3 &&
            rle[0].first == '1' &&
            rle[1].first == '/' &&
            rle[2].first == '2' &&
            rle[0].second == rle[2].second &&
            rle[1].second == 1
        ) ||
        s == "/"
    );
}
