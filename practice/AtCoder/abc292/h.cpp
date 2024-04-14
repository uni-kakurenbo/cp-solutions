/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include "template/standard.hpp"
/* #endregion */

#include "data_structure/lazy_segment_tree.hpp"
#include "algebraic/addition.hpp"

template<class T> using base = lib::algebraic::base<std::pair<T,T>>;

template<class T>
struct monoid : base<T>, lib::algebraic::associative {
    using base<T>::base;
    monoid() : base<T>::base({ 0, INT_MIN }) {}
    inline monoid operator+(const monoid& other) const {
        return monoid({
            this->val().first + other->first,
            std::max(this->val().second, this->val().first + other->second)
        });
    }
};

signed main() {
    int n, q; i64 b; cin >> n >> b >> q;
    vector<std::pair<i64,i64>> a(n);
    REP(i, n) {
        i64 v; input >> v;
        a[i] = { v - b, v - b };
    }

    lib::lazy_segment_tree<monoid<i64>> data(a);
    debug(data);

    REP(q) {
        i64 c, x; cin >> c >> x; --c;
        data[c] = spair<i64>{ x - b, x - b };
        debug(data);

        int i = data.max_right(0, [](auto s) { return s->second < 0; });
        if(i != n) i++;
        debug(i, data(0, i).fold());

        print(ld(data(0, i).fold()->first + b*i) / i);
    }
    return 0;
}
