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

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i64> s(n); input >> s;

    i64 beg = s[0];
    i64 end = s[-1];
    debug(beg, end);

    s.erase(s.begin());
    s.pop_back();

    s.sort();
    uni::multiset<i64> st(ALL(s));

    i64 cur = beg;
    i32 cnt = 2;
    until(cur * 2 >= end) {
        debug(cur, st);
        auto v = st.upper_bound(cur * 2);
        if(v == st.begin()) {
            print(-1);
            return;
        }
        --v;
        st.erase(v);
        cur = *v;
        ++cnt;
    }

    print(cnt);
}
