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
    i32 n, l; input >> n >> l;

    if(l % 3 != 0) {
        print(0);
        return;
    }

    vector<i64> d(n - 1); input >> d;
    uni::accumulation cum(d);
    debug(d, cum);
    REP(i, n) cum[i] %= l;
    cum.sort();

    // auto view = uni::views::concat(cum);
    // uni::vector<i64> a(ALL(view));
    auto a = cum;
    uni::counter<i64> cnt(cum);
    debug(a);

    std::set<array<i32, 3>> st;

    auto p = l/3;

    i64 ans = 0;

    REP(i, n) {
        ans += cnt[cum[i] + p] * cnt[cum[i] + 2 * p];
        // auto itr0 = a.lower_bound(a[i] + p);
        // auto itr1 = a.lower_bound(a[i] + 2 * p);
        // if(itr0 == a.end()) continue;
        // if(itr1 == a.end()) continue;
        // if(*itr0 != a[i] + p) continue;
        // if(*itr1 != a[i] + 2 * p) continue;

        // std::array<i32, 3> is = { itr0 - a.begin(), itr1 - a.begin(), i };
        // ITRR(v, is) v %= n;
        // std::ranges::sort(is);

        // debug(is);
        // st.insert(is);
    }

    // debug(st);
    // print(st.size());
    print(ans);
}
