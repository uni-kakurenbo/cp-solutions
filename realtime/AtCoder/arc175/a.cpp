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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint998244353;

void solve() {
    i32 n; input >> n;
    valarray<i32> p(n); input >> p;
    p -= 1;

    string s; input >> s;

    mint ans = 0;

    FOR(x, -1, 1, 2) {
        mint cnt = 1;

        vector<int> used(n);

        ITR(i, p) {
            if(used[lib::mod(i + x, n)]) {
                if(s[i] == '?') cnt *= 2;
            }
            else {
                if(s[i] == (x == 1 ? 'R' : 'L')) cnt *= 0;
            }
            used[i] = true;
        }

        ans += cnt;
    }

    print(ans);
}
