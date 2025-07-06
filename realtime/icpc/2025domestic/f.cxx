/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

// #include "template/debug.hpp"
// #include "snippet/aliases.hpp"
// #include <bits/stdc++.h>
// using namespace std;

using i32 = int;
using i64 = long;

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

#include "iterable/counter.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    if(n == 0) exit(0);
    string s, t; input >> s >> t;

    if(
        s.count('a') != t.count('a') ||
        s.count('b') != t.count('b')
    ) {
        print("no");
        return;
    }

    auto gather = s.count('a') - (s.find('b') - s.begin());
    string ans(gather, 'B');

    s.sort();

    uni::counter<char> cnt(s);

    char now = 'b';

    REPD(i, n) {
        if(now != t[i]) {
            if(cnt[now] > 0) ans += std::string(cnt[now], t[i]);
            cnt[t[i]]--;
            now = t[i];
        }
        else {
            cnt[now]--;
        }
        debug(now, cnt);
    }

    print("yes");
    print(uni::to_uppwer(ans));
}
