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
    i64 n; input >> n;

    lib::map<i64, i64> res;
    auto f = [&](auto&& f, i64 x) -> i64 {
        if(x < 2) return 0;
        if(res.contains(x)) return res[x];
        return res[x] = x + f(f, x / 2) + f(f, lib::div_ceil(x, 2L));
    };

    print(f(f, n));
}
