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
    i32 n, k; input >> n >> k;
    vector<i64> a(n); input >> a;

    auto ok = [&]() {
        uni::accumulation cum(a);
        debug(a, cum);
        auto itr = cum.lower_bound(k);
        REP(it, cum.begin(), itr) if(*it >= k) return false;
        REP(it, itr, cum.end()) if(*it < k) return false;
        return true;
    };

    a.sort();

    if(ok()) {
        print.yes();
        print(a);
        return;
    }

    a.reverse();

    if(ok()) {
        print.yes();
        print(a);
        return;
    }

    print.no();
}
