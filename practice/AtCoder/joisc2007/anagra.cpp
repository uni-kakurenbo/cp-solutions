/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    string s; input >> s;
    int n = s.size();

    lib::compressed<int> p(ALL(s));

    lib::factorial<u64> fact(26);
    lib::counter<int> cnt(p);

    debug(p, fact, cnt);

    u64 ans = 1;
    REP(i, n) {
        debug(p[i], n-i-1, fact(n-i-1));
        REP(v, p[i]) {
            if(cnt[v] < 1) continue;

            i64 prod = fact(n - i - 1);

            --cnt[v];
            REP(u, 26) prod /= fact(cnt[u]);
            ++cnt[v];
            debug(v, prod);
            ans += prod;
        }

        --cnt[p[i]];
    }

    print(ans);
}
