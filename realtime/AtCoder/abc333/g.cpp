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

#include "numeric/stern_brocot_tree.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using value = boost::multiprecision::cpp_int;

ld w;
spair<value> near(spair<value> p, spair<value> q) {
    if(p.first * q.second > q.first * p.second) return near(q, p);
    if(q.second * (p.second * w - p.first) <= p.second * (q.first - w * q.second)) {
        return { p.first, p.second };
    }
    else {
        return { q.first, q.second };
    }
}

void solve() {
    lib::stern_brocot_tree<value, value, value> tree;
}
