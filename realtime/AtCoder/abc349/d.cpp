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

#include "numeric/boundary_seeker.hpp"

void solve() {
    u64 l, r; input >> l >> r;

    vector<spair<u64>> ans;

    while(true) {
        auto ok = [&](i32 d) {
            if(std::countr_zero(l) < d) return false;
            u64 v = l >> d;
            u64 u = (v + 1) << d;
            return u <= r;
        };

        lib::boundary_seeker<i32> seeker(ok);

        i32 d = seeker.bound(0, 62);
        u64 nl = ((l >> d) + 1) << d;
        ans.emplace_back(l, nl);
        l = nl;
        if(l == r) break;
    }

    print(ans.size());
    print(ans);
}
