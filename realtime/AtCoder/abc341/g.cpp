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

#include "algebraic/helper.hpp"

#include "data_structure/segment_tree.hpp"

struct S {
    i64 sum = 0;
    i64 len = 0;
    i64 max = 0;
    i64 ml = 0;
    S(i64 sum, i64 len, i64 max, i64 ml) : sum(sum), len(len), max(max), ml(ml) {}
    S() = default;
};

S e() { return S{}; }
S op(S x, S y) {
    if(x.len == 0) return y;
    if(y.len == 0) return x;
    if(x.max * (x.len + y.ml) < (x.sum + y.max) * x.ml) {
        return {
            x.sum + y.sum,
            x.len + y.len,
            x.sum + y.max,
            x.len + y.ml
        };
    }
    else {
        return {
            x.sum + y.sum,
            x.len + y.len,
            x.max,
            x.ml
        };
    }
}

using monoid = lib::algebraic::monoid_helper<S, op, e>;

void solve() {
    int n; input >> n;
    valarray<i64> a(n); input >> a;
    lib::segment_tree<monoid> data(n);
    REP(i, n) data[i] = S{ a[i], 1, a[i], 1 };

    REP(i, n) {
        auto x = data(i, n).fold().val();
        print((ld)x.max / x.ml);
    }
}
