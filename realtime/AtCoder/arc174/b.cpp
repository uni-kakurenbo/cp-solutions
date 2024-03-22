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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/boundary_seeker.hpp"

void solve() {
    array<i64, 5> a, p; input >> a >> p;

    i64 b = -2 * a[0] - a[1] + a[3] + 2 * a[4];

    auto ok = [&](i64 k) {
        i64 c3, c4;
        if(p[4] < 2 * p[3]) {
            c4 = k / p[4];
            c3 = (k - k / p[4] * p[4]) / p[3];
        }
        else {
            c3 = k / p[3];
            c4 = (k - k / p[3] * p[3]) / p[4];
        }

        i64 c = c3 + c4 * 2;
        debug(k, c);
        return c >= -b;
    };

    lib::boundary_seeker<i64> seeker(ok);

    print(seeker.bound(INF64, -1));
}
