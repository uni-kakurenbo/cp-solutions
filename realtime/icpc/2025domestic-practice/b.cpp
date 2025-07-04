/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 0;
    while(true) {
        debug_("Case: #" + std::to_string($++));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    int n,m;
    std::cin >> n >> m;
    if(n == 0 && m == 0)exit(0);

    vector<i32> cnt(n);
    i32 ans = 0;

    vector<int> a(m), b(m);
    REP(i,m) cin >> a[i] >> b[i];
    a -= 1, b -= 1;

    REP(i, m) {
        cnt[b[i]]++;
        if(chmax(--cnt[a[i]], 0)) {
            ++ans;
        };
    }

    print(ans);
}
