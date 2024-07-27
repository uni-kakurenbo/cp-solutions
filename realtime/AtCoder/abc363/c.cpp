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
    i32 n, k; input >> n >> k;
    string s; input >> s; s.sort();

    i32 cnt = 0;

    do {
        auto found = false;
        FOR(i, n - k) {
            if(s.substr(i, k) == uni::reversed(s.substr(i, k))) {
                found = true;
            }
        }
        // debug(s, found);

        cnt += !found;
    } while(std::ranges::next_permutation(s).found);

    print(cnt);
}
