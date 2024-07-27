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

#include "template/warnings.hpp"
void solve() {
    i64 n; input >> n;

    auto f = [&](auto&& race, auto v, auto l, auto r) -> void {
        debug(v);
        auto s = std::to_string(v);

        if(std::ranges::count(s, '0') == 0 && s == uni::reversed(s)) {
            l += std::to_string(v);
            print(l + uni::reversed(r));
            exit(0);
        }

        auto ds = uni::divisors(v);
        debug(ds);

        ITR(d, ds) {
            if(d == 1) continue;

            auto str = std::to_string(d);
            if(std::ranges::count(str, '0') > 0) continue;

            auto rev = uni::reversed(str);

            auto m = d * std::stoll(rev);
            if(v % m != 0) continue;

            race(race, v / m, l + str + "*", r + str + "*");
        }
    };

    string l, r;
    f(f, n, l, r);

    print(-1);
}
