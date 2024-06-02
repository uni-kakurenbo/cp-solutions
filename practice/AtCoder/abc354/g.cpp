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

#include <atcoder/maxflow.hpp>

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<string> s(n); input >> s;
    vector<i64> a(n); input >> a;

    atcoder::mf_graph<i64> mf(2 * n + 2);
    i32 sv = 2 * n, tv = 2 * n + 1;

    REP(i, n) {
        mf.add_edge(sv, i, a[i]);
        mf.add_edge(n + i, tv, a[i]);
    }

    REP(i, n) REP(j, n) {
        if(s[i] == s[j]) {
            if(i < j) mf.add_edge(j, n + i, INF32);
        }
        else if(uni::is_continuous_subsequence_of(s[i], s[j])) {
            mf.add_edge(j, n + i, INF32);
        }
    }

    print(a.sum() - mf.flow(sv, tv));
}
