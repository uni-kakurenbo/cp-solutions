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
    i32 n, m; input >> n >> m;
    vector<i64> t(m), p(m); input >> uni::views::zip(t, p); p -= 1;

    uni::compressed comp(t);
    i32 l = comp.rank_sup();
    debug(comp, comp.values);

    uni::vector<i64> gain(l - 1);
    REP(i, l - 1) gain[i] = comp.values[i + 1] - comp.values[i];
    debug(gain);

    vector<i32> n(-1);
}
