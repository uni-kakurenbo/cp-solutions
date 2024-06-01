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
#include "data_structure/segment_tree_rooter.hpp"

using mint = uni::static_builtin_modint_32bit<100>;


auto query(i32 i, u32 j) {
    debug(uni::shiftl(j, i), uni::shiftl(j + 1, i));
    print("?", i, j); std::cout << std::flush;
    i32 sum; input >> sum;
    return sum;
}

void solve(i32 l, i32 r) {
    i32 n, l, r; input >> n >> l >> r; ++r;

    vector<spair<i32>> rs;
    while(l != r) {
        i32 i = 0;
        while(l % uni::shiftl(1UL, i + 1) == 0 and l + (i32)uni::shiftl(1UL, i + 1) <= r) {
            i += 1;
        }
        debug(l, l + uni::shiftl(1UL, i));
        i32 p = i;
        rs.emplace_back(p, l >> p);
        l += uni::shiftl(1UL, i);
    }

    uni::static_builtin_modint_32bit<100> sum = 0;
    ITR(x, y, rs) {
        sum += query(x, y);
    }

    print("!", sum.val());
}
