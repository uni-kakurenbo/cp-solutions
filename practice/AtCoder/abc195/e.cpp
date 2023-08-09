/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    string s, x; cin >> s >> x;

    array<int,7> ok;
    ok.fill(0);
    ok[0] = 1;

    s.reverse(), x.reverse();
    valarray<int> a(n); REP(i, n) a[i] = s[i] - '0';

    char prev = 'T';
    REP(i, n) {
        if(prev != x[i]) REP(r, 7) ok[r] ^= 1;
        array<int,7> nxt; nxt.fill(0);
        REP(r, 7) {
            int v0 = lib::mod(r * SINV<10,7>, 7);
            int v1 = lib::mod((r - a[i]) * SINV<10,7>, 7);
            debug(r, v0, v1);
            nxt[v0] |= ok[r], nxt[v1] |= ok[r];
        }
        ok = std::move(nxt);
        debug(ok);
        prev = x[i];
    }
    if(prev != 'T') REP(r, 7) ok[r] ^= 1;

    print(ok[0] ? "Takahashi" : "Aoki");
}
