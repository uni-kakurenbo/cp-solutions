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
#include "numeric/numerical_sequence.hpp"

namespace ns = lib::numerical_sequence;

void solve() {
    i64 n; input >> n;

    auto ok = [&](i64 v) {
        return ns::arithmetic<i64>(ns::static_term<i64,0>(1), ns::common_difference<i64>(1)).sum(v) <= n;
    };

    lib::boundary_seeker<i64> seeker(ok);
    print(seeker.bound(0));
}
