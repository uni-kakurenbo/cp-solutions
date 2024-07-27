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
    i32 n; input >> n;
    vector<i64> l(n), r(n); input >> uni::views::zip(l, r);

    auto can = l.sum() <= 0 && 0 <= r.sum();
    if(can) {
        auto v = l;
        auto s = v.sum();
        debug(s);

        REP(i, n) {
            auto take = uni::max(0, uni::min(r[i] - v[i], -s));
            s += take;
            v[i] += take;
        }
        debug(s);

        print.yes();
        print(v);
        REP(i, n) {
            assert(l[i] <= v[i] && v[i] <= r[i]);
        }
        assert(v.sum() == 0);
    }
    else {
        print.no();
    }
}
