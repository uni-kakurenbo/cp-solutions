/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "data_structure/segment_tree.hpp"
#include "data_structure/monoid/addition.hpp"

template<class T> using base = lib::monoids::base<std::pair<T,T>>;

template<class T>
struct monoid : base<T> {
    using base<T>::base;
    monoid() : base<T>::base({ 0, INT_MIN }) {}
    inline monoid operator*(const monoid& other) const {
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

    lib::segment_tree<monoid<i64>> data(ALL(a));
    debug(data);

    print << fixed << std::setprecision(20);
    REP(q) {
        i64 c, x; cin >> c >> x; --c;
        data.set(c, { x - b, x - b });
        debug(data);

        int i = data.max_right(0, [](auto s) { return s->second < 0; });
        if(i != n) i++;
        debug(i, data.prod(0, i));

        print(ld(data.prod(0, i).first + b*i) / i);
    }
    return 0;
}
