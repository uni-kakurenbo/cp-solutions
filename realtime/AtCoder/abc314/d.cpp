/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 17 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/range_set_range_sum.hpp"

void solve() {
    int n; cin >> n;
    std::string s; cin >> s;

    lib::lazy_segment_tree<lib::actions::range_set_range_sum<int>> chr(n, 1);

    bool cap = false;
    REP(i, n) if('a' <= s[i]) chr[i] = 0;
    debug(chr);

    s = lib::to_lower(s);

    int q; cin >> q;
    REP(q) {
        int t; cin >> t;
        int x; cin >> x; --x;
        char c; cin >> c;
        if(t == 1) {
            if(std::islower(c) ^ (!cap)) chr[x] = 1;
            else chr[x] = 0;
            s[x] = ::tolower(c);
        }
        if(t == 2) {
            cap = false;
            chr(0, n) <<= 0;
        }
        if(t == 3) {
            cap = true;
            chr(0, n) <<= 0;
        }
        DEBUG(ALL(s));
        debug(cap, chr);
    }

    string t;
    REP(i, n) {
        if((!cap) ^ bool(chr[i].val())) t += s[i];
        else t += toupper(s[i]);
    }

    print(t);
}
