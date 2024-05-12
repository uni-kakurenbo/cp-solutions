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

#include "hash/sequence_hasher.hpp"

void solve() {
    i32 n; input >> n;
    vector<string> s(n); input >> s;

    map<uni::sequence_hasher<>::hash_type, i32> cnt;

    i64 ans = 0;

    REP(i, n) {
        uni::sequence_hasher<> hash(ALL(s[i]));

        FOR(j, 1, s[i].ssize()) {
            ans += cnt[hash.get(0, j)];
            debug(s[i], cnt[hash.get(0, j)], j);
        }

        FOR(j, 1, s[i].ssize()) {
            cnt[hash.get(0, j).val()]++;
        }
    }

    print(ans);
}
