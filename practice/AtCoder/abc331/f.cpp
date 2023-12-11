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

#include "data_structure/segment_tree.hpp"
#include "action/helpers.hpp"

using mint = lib::static_modint_64bit<(1UL << 61) - 1>;

// struct hash {
//     mint val, rev, pow;
// };

// hash op(hash p, hash q) {
//     return {
//         p.val + q.val * pow * 10
//         q.rev * pow
//         p.len + q.len
//     };
// }

void solve() {
    int n, q; input >> n >> q;
    string s; input >> s;
    debug(mint::is_prime);
    debug(mint{10}.pow(1000));

    lib::modint64 a = 0;
    debug(a);
    debug(lib::modint64::bit_length);
}
