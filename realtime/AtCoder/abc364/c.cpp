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
    i64 n, x, y; input >> n >> x >> y;
    vector<i64> a(n), b(n); input >> a >> b;

    vector<i32> ids(n); std::iota(ALL(ids), 0);

    i32 ans = n;
    REP(2) {
        ids.sort([&](i32 i, i32 j) { return a[i] > a[j]; });

        i64 s = 0, t = 0;
        ITR(j, i, ids | uni::views::enumerate) {
            debug(i, j);

            s += a[i], t += b[i];
            if(s > x || t > y) {
                chmin(ans, j + 1);
            }
        }

        std::swap(a, b);
        std::swap(x, y);
    }

    print(ans);
}
