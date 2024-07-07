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

#include "data_structure/lazy_segment_tree.hpp"

using mint = uni::modint998244353;

struct S {
    mint c0, c1, c2, c3;
};

struct F {
    mint x, y;
};

S op(S x, S y) {
    return {
        x.c0 + y.c0,
        x.c1 + y.c1,
        x.c2 + y.c2,
        x.c3 + y.c3
    };
}

S e() { return { 0, 0, 0, 0 }; }

S mapping(F f, S x) {
    return {
        x.c0 + f.x * x.c2 + f.y * x.c1 + f.x * f.y * x.c3,
        x.c1 + f.x * x.c3,
        x.c2 + f.y * x.c3,
        x.c3
    };
}

F composition(F g, F f) {
    return {
        f.x + g.x,
        f.y + g.y
    };
}

F id() { return { 0, 0 }; }

using action = uni::actions::helper<S, op, e, F, mapping, composition, id>;

#include "template/warnings.hpp"
void solve() {
    i32 n, q; input >> n >> q;
    vector<mint> a(n), b(n); input >> a >> b;

    uni::lazy_segment_tree<action> data(n);
    REP(i, n) data[i] = { a[i] * b[i], a[i], b[i], 1 };

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i32 l, r, x; input >> l >> r >> x; --l;
            data(l, r) *= { x, 0 };
        }
        if(t == 2) {
            i32 l, r, x; input >> l >> r >> x; --l;
            data(l, r) *= { 0, x };
        }
        if(t == 3) {
            i32 l, r; input >> l >> r; --l;
            print(data(l, r).fold()->c0);
        }
    }
}
