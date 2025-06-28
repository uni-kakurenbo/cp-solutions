/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "template/warnings.hpp"
void solve() {
    using modint = uni::dynamic_barrett_modint_64bit<-1>;
    i64 a, x, m; input >> a >> x >> m;
    modint::set_mod(m);

    auto r = uni::sqrt_floor(x);
    debug(r);

    modint ans = 0;

    modint sum = 0;
    modint p = 1;
    REP(r) {
        sum += p;
        p *= a;
    }

    modint q = 1;
    debug(sum, q);

    REP(r) {
        ans += sum;
        sum *= p;
        q *= p;
    }

    debug(ans);
    debug(x, r * r, q);

    REP(x - r * r) {
        ans += q;
        q *= a;
    }

    print(ans);
}
