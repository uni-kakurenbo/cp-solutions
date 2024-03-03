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

struct S {
    i64 x, y, z;
};

spair<i64> volume(S a, S b) {
    i64 ab = lib::max(0, lib::min(a.x + 7, b.x + 7) - lib::max(a.x, b.x)) * lib::max(0, lib::min(a.y + 7, b.y + 7) - lib::max(a.y, b.y)) * lib::max(0, lib::min(a.z + 7, b.z + 7) - lib::max(a.z, b.z));
    return { 343 * 2 - lib::max(0, 2 * ab), ab };
}

std::tuple<i64, i64, i64> volume(S a, S b, S c) {
    i64 abc = lib::max(0, lib::min(a.x + 7, b.x + 7, c.x + 7) - lib::max(a.x, b.x, c.x)) * lib::max(0, lib::min(a.y + 7, b.y + 7, c.y + 7) - lib::max(a.y, b.y, c.y)) * lib::max(0, lib::min(a.z + 7, b.z + 7, c.z + 7) - lib::max(a.z, b.z, c.z));
    auto [ _ab, ab ] = volume(a, b);
    auto [ _bc, bc ] = volume(b, c);
    auto [ _ca, ca ] = volume(c, a);
    return { 343 * 3 - 2 * (ab + bc + ca) + 3 * abc, ab + bc + ca - 3 * abc, abc, };
}

void solve() {
    tuple<i64, i64, i64> v; input >> v;

    debug(volume({ 0, 0, 0 }, { 0, 6, 0 }, { 7, 0, 0 }));

    FOR(a0, -7, 7) FOR(b0, -7, 7) FOR(c0, -7, 7) {
        FOR(a1, -7, 7) FOR(b1, -7, 7) FOR(c1, -7, 7) {
            if(volume({ 0, 0, 0 }, { a0, b0, c0 }, { a1, b1, c1 }) == v) {
                print.yes();
                print(0, 0, 0, a0, b0, c0, a1, b1, c1);
                return;
            }
        }
    }
    print.no();
}
