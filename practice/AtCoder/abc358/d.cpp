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
    vector<i64> a(n), b(m); input >> a >> b;

    uni::multiset<i32> st(ALL(a));
    i64 ans = 0;

    b.sort().reverse();
    ITR(v, b) {
        auto p = st.next(v);
        if(!p) {
            print(-1);
            return;
        }
        ans += *p;
        st.remove(*p);
    }

    print(ans);
}
