/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    std::string s; input >> s;
    std::string t; input >> t;

    int x = 0;
    auto f = [&](string v) {
        if(v[0] > v[1]) std::swap(v[0], v[1]);
        if(v == "AB") return 1;
        if(v == "BC") return 1;
        if(v == "CD") return 1;
        if(v == "DE") return 1;
        if(v == "AE") return 1;
        return 2;
    };

    print.yesno(f(s) == f(t));
}
