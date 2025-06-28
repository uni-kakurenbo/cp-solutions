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
    i32 n, q; input >> n >> q;

    vector<i64> table(n), rev(n);
    std::iota(ALL(table), 0);
    std::iota(ALL(rev), 0);

    vector<i32> hato(n);
    std::iota(ALL(hato), 0);

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i32 a, b; input >> a >> b; --a, --b;
            hato[a] = rev[b];
        }
        if(t == 2) {
            i32 a, b; input >> a >> b; --a, --b;
            a = rev[a], b = rev[b];
            std::swap(table[a], table[b]);
            rev[table[a]] = a, rev[table[b]] = b;
        }
        if(t == 3) {
            i32 a; input >> a; --a;
            print(table[hato[a]] + 1);
        }
    }
}
