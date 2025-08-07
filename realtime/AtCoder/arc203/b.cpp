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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i32> a(n), b(n); input >> a >> b;

    if(a.sum() != b.sum()) {
        print.no();
        return;
    }

    if(a.sum() == 1) {
        if(a[0] == 1 || b[0] == 1) {
            print.yesno(a == b);
            return;
        }
        if(a[-1] == 1 || b[-1] == 1) {
            print.yesno(a == b);
            return;
        }
        print.yes();
        return;
    }

    print.yes();
}
