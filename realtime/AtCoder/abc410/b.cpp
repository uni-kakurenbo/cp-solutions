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
    i32 n, q; input >> n >> q;
    vector<i64> x(q); input >> x;

    vector<i64> ball(n);

    ITR(v, x) {
        if(v == 0) {
            auto m = ball.min();
            REP(i, n) {
                if(ball[i] == m) {
                    print(i + 1);
                    ball[i]++;
                    break;
                }
            }
        }
        else {
            ball[v - 1]++;
            print(v);
        }
    }
}
