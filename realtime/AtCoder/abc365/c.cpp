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

#include "numeric/boundary_seeker.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, m; input >> n >> m;
    vector<i64> a(n); input >> a;

    auto ok = [&](i128 x) {
        i128 sum = 0;
        ITR(v, a) sum += uni::min(v, x);
        return sum <= m;
    };

    uni::boundary_seeker<i128> seeker(ok);
    const auto bound = seeker.bound(0, INF64 + 1);
    debug(bound);
    if(bound >= INF64) {
        print("infinite");
    }
    else {
        print(bound);
    }
}
