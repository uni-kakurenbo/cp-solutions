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

#include "iterable/count_inversion.hpp"

void solve() {
    int n; input >> n;
    string s; input >> s;

    std::vector<i64> a = { 0 };
    i64 max = 0;
    REP(i, n - 1) {
        i64 nxt = 0;
        if(s[i] == '<') nxt = a.back() + n;
        if(s[i] == '>') nxt = a.back() - 1;
        a.push_back(nxt);
        chmax(max, nxt);
    }
    debug(a);

    auto ans = lib::inversion<true,i64>::count_with_compression(ALL(a));
    print(ans);
}
