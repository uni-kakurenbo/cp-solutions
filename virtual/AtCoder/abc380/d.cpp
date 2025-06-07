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
    string s; input >> s;
    i64 n = s.ssize();

    auto inv = [&](auto&& self, u64 sec) {
        if(sec == 0) return false;
        return !self(self, sec - std::bit_floor(sec));
    };

    i64 q; input >> q;
    REP(q) {
        i64 k; input >> k; --k;

        i64 sec = k / n;
        debug(k, sec);

        bool cap = inv(inv, sec);
        auto chr = s[(k % n)];

        debug(cap, chr);

        debug(cap, (bool)std::isupper(chr));
        cap = cap ^ (bool)std::isupper(chr);


        if(cap) {
            print((char)std::toupper(chr));
        }
        else {
            print((char)std::tolower(chr));
        }
    }
}
