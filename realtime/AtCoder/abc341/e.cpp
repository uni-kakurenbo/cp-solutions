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

#include "data_structure/lazy_segment_tree.hpp"
#include "action/helpers.hpp"

struct S {
    int l = -1;
    int r = -1;
    int valid = true;
    S(int l, int r, int valid) : l(l), r(r), valid(valid) {}
    S(int v, int valid) : l(v), r(v), valid(valid) {}
    S() = default;

    pair<spair<int>, int> _debug() const { return { spair<int>{ l, r }, valid }; }
};

S e() { return S{}; }
S op(S x, S y) {
    if(x.l == -1) return y;
    if(y.l == -1) return x;
    return { x.l, y.r, x.r != y.l and x.valid and y.valid };
}

S mp(int f, S x) {
    if(x.l == -1) return x;
    return { x.l != f, x.r != f, x.valid };
}
int comp(int f, int g) { return f != g; }
int id() { return 0; }

using action = lib::actions::helper<S, op, e, int, mp, comp, id>;

void solve() {
    int n, q; input >> n >> q;
    string s; input >> s;

    lib::lazy_segment_tree<action> data(n, S{ 0, 0, true });

    REP(i, n) data[i] += s[i] == '1';
    debug(data);

    REP(q) {
        int t, l, r; input >> t >> l >> r; --l;
        if(t == 1) {
            data(l, r) += 1;
        }
        if(t == 2) {
            debug(data(l, r).fold());
            print.yesno(data(l, r).fold().val().valid);
        }
        debug(data);
    }
}
