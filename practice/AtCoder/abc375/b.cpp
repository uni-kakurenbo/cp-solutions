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
    using point = uni::point<ld>;

    i64 n; input >> n;
    vector<point> ps(n); input >> ps;

    point p{};
    ld sum = 0;
    ITR(x, ps) sum += uni::distance(x, p), p = x;
    sum += uni::distance(p, { 0, 0 });
    print(sum);
}
