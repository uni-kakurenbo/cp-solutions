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
    i32 n, l; input >> n >> l;
    i32 k; input >> k;
    vector<i32> a(n); input >> a;
    a.push_back(l);

    auto ok = [&](i32 v) {
        i32 cur = 0;
        i32 cnt = 0;

        FOR(i, n) {
            if(a[i] - cur >= v) cur = a[i], ++cnt;
        }

        debug(v, cnt);

        return cnt > k;
    };

    lib::boundary_seeker<i32> seeker(ok);
    print(seeker.bound(0));
}
