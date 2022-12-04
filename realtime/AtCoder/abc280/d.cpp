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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

#include "numeric/boundary_seeker.hpp"

template <typename T>
unordered_map<T,int> prime_factor(T n) {
    unordered_map<T,int> ret;
    for (T i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        T tmp = 0;
        while (n % i == 0) {
            tmp++;
            n /= i;
        }
        ret[i] = tmp;
    }
    if (n != 1) ret[n] = 1;
    return ret;
}

signed main() {
    ll k; cin >> k;
    auto facts = prime_factor(k);

    ll ans = 0;
    ITRM(p, c, facts) {
        auto valid = [&](ll v) -> bool {
            ll res = 0, q = 1;
            while(q <= v) {
                q *= p;
                res += v/q;
            }
            return res < c;
        };
        Lib::BoundarySeeker<ll> seeker(valid);
        ll res = seeker.bound(1);
        debug(p, c, res);
        chmax(ans, res+1);
    }

    print(ans);

    return 0;
}
