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
    vector<i64> a(n); input >> a;

    uni::inverse inv(a);

    i64 sum = 0;
    i64 cur = 0;
    {
        uni::map<i64, i32> st;
        REP(i, n) {
            st[a[i]]++;
            cur += st.size();
        }
    }

    REP(i, n) {
        debug(sum, cur);
        sum += cur;

        auto itr = inv[a[i]].upper_bound(i);
        if(itr == inv[a[i]].end()) {
            cur -= n - i;
        }
        else {
            cur -= *itr - i;
        }
    }

    print(sum);
}
