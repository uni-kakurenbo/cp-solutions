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
    i32 n, t; input >> n >> t;
    vector<i64> a(t); input >> a; a -= 1;

    uni::vector<i32> row(n), col(n);
    i32 xs = 0, ys = 0;

    ITR(p, v, a | uni::views::enumerate) {
        i32 i = v / n, j = v % n;
        row[i]++;
        col[j]++;
        if(i == j) xs++;
        if(i == n - j - 1) ys++;

        if(
            row[i] == n ||
            col[j] == n ||
            xs == n ||
            ys == n
        ) {
            print(p + 1);
            exit(0);
        }
    }

    print(-1);
}
