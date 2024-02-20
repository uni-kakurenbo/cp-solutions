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

#include "numeric/boundary_seeker.hpp"

void solve() {
    i64 n, m, k; input >> n >> m >> k;

    auto valid = [&](i64 v) {
        i64 p = v / n;
        i64 q = v / m;
        i64 r = v / std::lcm(n, m);

        debug(v, p, q, r);

        return p + q - 2 * r < k;
    };

    lib::boundary_seeker<i64> seeker(valid);
    print(seeker.bound(0) + 1);
}
