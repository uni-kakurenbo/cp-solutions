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

i64 extGCD(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}

i64 MAX = 1'000'000'000'000'000'000L;

void solve() {
    i64 x, y; input >> x >> y;
    if(y == 0) {
        if(std::abs(x) == 1) print(0, 2);
        else if(std::abs(x) == 2) print(0, 1);
        else print(-1);
        return;
    }
    if(x == 0) {
        if(std::abs(y) == 1) print(2, 0);
        else if(std::abs(y) == 2) print(1, 0);
        else print(-1);
        return;
    }

    if(2 % std::gcd(x, y) != 0) {
        print(-1);
        return;
    }

    i64 a = 0, b = 0;
    extGCD(x, -y, b, a);
    a *= 2 / std::gcd(x, y), b *= 2 / std::gcd(x, y);

    i64 g = std::gcd(x, y);
    x /= g, y /= g;

    print(a, b);
}
