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
    a.sort();

    i64 max = a.back();

    i64 ans = 0;

    i64 prev = -1, pval = 0;
    ITR(i, v, a | uni::views::enumerate) {
        i64 cnt = 0;

        if(v == prev) {
            cnt = --pval;
        }
        else {
            auto span = a | std::views::drop(i + 1);

            for(i64 x = v; x <= max; x += v) {
                cnt += span.end() - std::ranges::lower_bound(span, x);
            }
        }


        ans += (pval = cnt);
        prev = v;
    }

    print(ans);
}
