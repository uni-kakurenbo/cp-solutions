/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; input >> n;
    string a; input >> a;

    lib::run_length rle(ALL(a));

    i64 ans = 0;

    lib::unordered_map<int, int> max;
    ITR(v, c, rle) {
        chmax(max[v], c);
    }
    debug(max);

    ITR(v, c, max) ans += c;

    print(ans);
}
