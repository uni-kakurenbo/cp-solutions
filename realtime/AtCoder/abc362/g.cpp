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

#include <atcoder/string>

#include "template/warnings.hpp"
#include "hash/sequence_hasher.hpp"
#include "numeric/boundary_seeker.hpp"

void solve() {
    std::string s; input >> s;
    i32 n = s.size();

    i32 q; input >> q;
    vector<string> t(q); input >> t;

    auto sa = atcoder::suffix_array(s);
    debug(sa);

    REP(i, q) {
        auto ok0 = [&](i32 v) {
            if(v < 0) return true;
            return s.substr(sa[v], t[i].size()) < t[i];
        };

        auto ok1 = [&](i32 v) {
            if(v < 0) return true;
            return s.substr(sa[v], t[i].size()) <= t[i];
        };

        uni::boundary_seeker<i32> seeker0(ok0), seeker1(ok1);
        debug(seeker0.bound(-1, n), seeker1.bound(-1, n));

        print(seeker1.bound(-1, n) - seeker0.bound(-1, n));
    }
}
