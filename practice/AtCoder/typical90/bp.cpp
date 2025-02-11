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

#include "data_structure/segment_tree.hpp"
#include "algebraic/affine.hpp"
#include "algebraic/combined.hpp"

void solve() {
    i32 n, q; input >> n >> q;

    uni::segment_tree<uni::algebraic::combined<uni::algebraic::affine<i64>, uni::algebraic::affine<i64, true>>> fs(n - 1);
    uni::segment_tree<uni::algebraic::addition<i32>> cnt(n - 1);

    REP(q) {
        i32 t, x, y, v; input >> t >> x >> y >> v;
        --x, --y;

        if(t == 0) {
            cnt[x] += 1;
            fs[x] = std::make_pair(-1, v);
        }
        if(t == 1) {
            bool rev = false;
            if(x > y) std::swap(x, y), rev = true;

            if(cnt(x, y).fold().val() < y - x) {
                print("Ambiguous");
            }
            else {
                i64 a, b;
                if(rev) std::tie(a, b) = fs(x, y).fold()->first.val();
                else std::tie(a, b) = fs(x, y).fold()->second.val();
                print(a * v + b);
            }
        }

        debug(fs, cnt);
    }
}
