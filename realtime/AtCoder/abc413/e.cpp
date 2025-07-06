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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/dynamic_sequence.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    auto m = 1UL << n;
    vector<i64> p(m); input >> p;

    uni::dynamic_sequence<i64> a(ALL(p));

    REP(d, n) {
        auto w = 1UL << d;

        REP(i, 0, m, w * 2) {
            debug(i, a[i], a[i + w]);
            if(a[i] > a[i + w]) {
                a.swap_ranges({ i, i + w }, { i + w, i + 2 * w });
            }
        }

        debug(a);
    }

    print(a);
}
