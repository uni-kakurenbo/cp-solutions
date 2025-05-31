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
    i32 n, m; input >> n >> m;
    vector<i64> a(n), b(m); input >> a >> b;

    multiset<spair<i64>> c;
    REP(i, m) c.emplace(b[i], i);

    vector<i32> ans(m, -1);

    REP(i, n) {
        while(true) {
            auto itr = c.lower_bound(std::make_pair(a[i], 0L));
            if(itr == c.end()) break;
            ans[itr->second] = i + 1;
            c.erase(itr);
        }
    }

    print(ans);
}
