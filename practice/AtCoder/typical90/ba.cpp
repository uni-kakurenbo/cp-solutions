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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/extremum_seeker.hpp"

#include "template/warnings.hpp"

i32 query(i32 i) {
    print("?", i); std::cout << std::flush;
    i32 r; input >> r;
    return r;
}

void solve() {
    vector<i64> a = { 1, 2, 3 };
    debug(a, a.size());
    i32 n; input >> n;

    uni::extremum_seeker<i32(i32)> seeker(query);
    print("!", seeker.max(1, n)); std::cout << std::flush;
}
