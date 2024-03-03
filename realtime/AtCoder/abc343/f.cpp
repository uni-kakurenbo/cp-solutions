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

struct S {
    int m0 = -1, c0 = 0;
    int m1 = -2, c1 = 0;
    S() = default;
    S(int m0, int c0, int m1, int c1) : m0(m0), c0(c0), m1(m1), c1(c1) {}
    S(int x) : S(x, 1, -1, 0) {}
    std::tuple<int, int, int, int> _debug() { return { m0, c0, m1, c1 }; }
};

S op(S x, S y) {
    map<int, int> cnt;
    cnt[x.m0] += x.c0;
    cnt[x.m1] += x.c1;
    cnt[y.m0] += y.c0;
    cnt[y.m1] += y.c1;
    cnt[-1] += 0;
    return S{ cnt.max_element()->first, cnt.max_element()->second, std::next(cnt.rbegin())->first, std::next(cnt.rbegin())->second };
}

S e() { return S{}; }

void solve() {
    int n, q; input >> n >> q;
    valarray<int> a(n); input >> a;

    lib::segment_tree<lib::algebraic::monoid_helper<S, op, e>> data(a);
    REP(q) {
        int t; input >> t;
        if(t == 1) {
            int p, x; input >> p >> x; --p;
            data[p] = S{x};
        }
        if(t == 2) {
            int l, r; input >> l >> r, --l;
            print(data(l, r).fold()->c1);
        }
    }
}
