/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
#include "output.hpp"

#include <atcoder/segtree>
using namespace atcoder;

Output print;

ll e() { return 0; }

signed main() {
    int q; cin >> q;

    segtree<ll,gcd<ll,ll>,e> st(100001);

    int l = 0, r = 0;
    LOOP(q) {
        int t; cin >> t;
        if(t == 1) {
            int  x; cin >> x;
            st.set(r++, x);
        }
        if(t == 2) {
            print(st.prod(l++, r));
        }
    }

    return 0;
}
