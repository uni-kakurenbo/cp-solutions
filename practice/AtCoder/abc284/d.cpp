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

#include "numeric/prime.hpp"

signed main() {

    int t; cin >> t;

    REP(t) {
        ll n; cin >> n;
        auto facts = lib::factorize(n);
        debug(facts);
        if(facts.begin()->second == 2) print(facts.begin()->first, std::next(facts.begin())->first);
        else print(std::next(facts.begin())->first, facts.begin()->first);
    }

    return 0;
}
