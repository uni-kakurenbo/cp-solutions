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

using mint = uni::modint998244353;

void solve() {
    i32 n, k; input >> n >> k;
    string s; input >> s;

    i64 init = s.count('?');

    vector<i32> ps;
    vector<array<std::bitset<1000>, 2>> fix(1UL << k);

    REP(x, 1UL << k) {
        string t;
        REP(i, k) t += "AB"[uni::bit(x, i)];
        if(t != uni::reversed(t)) continue;
        ps.push_back(x);
        debug(t);

        ITR(w, s | uni::views::slide(k)) {
            bool ng = true;
            REP(i, k) {
                if(w[i] != '?' && (w[i] == 'B') != uni::bit(x, i)) {
                    ng = false;
                }
            }
            if(ng) REP(i, k) {
                if(w[i] == '?') fix[x][uni::bit(x, i)].set(i);
            }
        }
        debug(fix[x]);
    }
    debug(ps);

    mint ans = 0; //MINT<2>.pow(init);

    REP(x, 1UL << ps.size()) {
        array<std::bitset<1000>, 2> st;
        REP(i, ps.size()) {
            if(uni::bit(x, i)) st[0] |= fix[ps[i]][0], st[1] |= fix[ps[i]][1];
        }

        debug(x, (st[0] & st[1]).count());

        ans += (std::popcount(x) % 2 * 2 - 1) * MINT<2>.pow(init - (st[0] & st[1]).count());
    }

    print(ans);
}
