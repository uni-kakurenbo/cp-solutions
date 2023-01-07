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

template <typename T>
vector<pair<T, T>> prime_factor(T n) {
    vector<pair<T, T>> ret;
    for (T i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        T tmp = 0;
        while (n % i == 0) {
            tmp++;
            n /= i;
        }
        ret.push_back(make_pair(i, tmp));
    }
    if (n != 1) ret.push_back(make_pair(n, 1));
    return ret;
}

signed main() {
    ll n; cin >> n;

    auto facts = prime_factor(n);

    ll ans = 0;

    ITR(fact, cnt, facts) {
        debug(fact, cnt);
        ll k = 0, i = 1;
        while(true) {
            if(i*(i+1)/2 <= cnt) k = i;
            else break;
            ++i;
        }
        ans += k;
    }

    print(ans);

    return 0;
}
