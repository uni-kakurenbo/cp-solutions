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
    vector<string> s(n); input >> s;
    unordered_set<string> t;
    REP(m) { t.insert(input.one<string>()); }

    debug(s, t);

    stack<pair<bitset<8>, string>> stk;
    stk.emplace(0, "");

    while(!stk.empty()) {
        auto [p, cur] = stk.top(); stk.pop();
        if(cur.size() > 16) continue;

        if(p.count() == n-1) {
            int pos = 0;
            while(p.test(pos)) ++pos;
            cur += s[pos];

            auto sz = cur.size();
            if(sz < 3 || 16 < sz) continue;
            if(t.contains(cur)) continue;

            print(cur);
            return;
        }

        REP(i, n) {
            if(p.test(i)) continue;
            FOR(j, 1, 16 - cur.ssize()) {
                stk.emplace(p | bitset<8>().set(i), cur + s[i] + string(j,'_'));
            }
        }
    }

    print(-1);
}
