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
    vector<std::bitset<10>> s(n);
    ITRR(v, s) {
        string x; input >> x;
        REP(i, m) v[i] = x[i] == 'o';
    }

    i32 ans = m;

    vector<i32> p(n); std::iota(ALL(p), 0);
    do {
        std::bitset<10> st;
        ITR(t, i, p | uni::views::enumerate) {
            st |= s[i];
            if(st.count() == m) chmin(ans, t + 1);
        }
    } while(std::ranges::next_permutation(p).found);

    print(ans);
}
