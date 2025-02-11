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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/repeater.hpp"

void solve() {
    i64 n, k; input >> n >> k;

    auto f = [&](i32 x) { return (x + lib::to_base_n_vector(x, 10).sum()) % 100000; };

    lib::repeater<i64, 100000> apply(f);
    print(apply[k](n));
}
