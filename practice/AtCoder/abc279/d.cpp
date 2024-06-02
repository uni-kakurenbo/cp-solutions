/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include "template/standard.hpp"
/* #endregion */

#include "numeric/extremum_seeker.hpp"

signed main() {
    i64 a, b; cin >> a >> b;

    auto f = [&](i64 t) -> ld {
        return a / std::sqrt(t + 1) + 1.0 * b * t;
    };

    uni::extremum_seeker<ld(i64)> seeker(f);
    debug(seeker.arg_min(0));
    print(seeker.min(0));

    return 0;
}
