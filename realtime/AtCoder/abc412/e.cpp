/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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


#include "template/warnings.hpp"
void solve() {
    i64 l, r; input >> l >> r; l++;

    auto rt = uni::sqrt_ceil(r);

    valarray<bool> isprime(rt + 1, true);
    valarray<bool> isprime2(r - l + 1, true);

    for(i64 p = 2; p * p <= r; ++p) {
        if (!isprime[p]) continue;
        for (i64 q = p * 2; q * q <= r; q += p) {
            isprime[q] = false;
        }

        i64 start = (l + p - 1) / p * p;
        if (start == p) start = p * 2;

        for (i64 q = start; q <= r; q += p) {
            isprime2[q - l] = false;
        }
    }

    vector<i64> inc(r - l + 1);
    FOR(i, r - l) inc[i] = isprime2[i];

    REP(x, 2L, rt) {
        if(!isprime[x]) continue;
        i64 p = x;
        if(l <= p && p <= r) assert(isprime2[p - l]);
        while(p <= r) {
            if(p >= l) inc[p - l]++;
            p *= x;
        }
    }
    // debug(inc);

    print(r - l + 1 - inc.count(0) + 1);
}
