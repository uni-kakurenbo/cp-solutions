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


constexpr std::array<std::array<i32, 5>, 3> V = {
    std::array<i32, 5>{ 0, 0, 0, 0, 0 },
    std::array<i32, 5>{ 0, 2, 3, 3, 4 },
    std::array<i32, 5>{ 0, 3, 6, 7, 8 },
};

#include "template/warnings.hpp"
void solve() {

    auto f = [&](i64 x, i64 y) {
        i64 tq = x / 4, tr = x % 4;
        i64 sq = y / 2, sr = y % 2;

        i64 res = 8 * tq * sq;
        res += V[sr][4] * tq;
        res += V[2][tr] * sq;
        res += V[sr][tr];

        return res;
    };

    i64 a, b, c, d; input >> a >> b >> c >> d;
    if(a < 0) {
        i64 t = uni::div_ceil(-a, 4L) * 4;
        a += t, c += t;
    }
    if(b < 0) {
        i64 t = uni::div_ceil(-b, 2L) * 2;
        b += t, d += t;
    }
    debug(a, b, c, d);

    print(f(c, d) - f(a, d) - f(c, b) + f(a, b));
}
