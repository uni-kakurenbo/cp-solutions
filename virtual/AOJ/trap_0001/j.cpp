/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include <atcoder/lazysegtree.hpp>
#include "template/warnings.hpp"

#include <iostream>
using namespace std;

#include <atcoder/modint>
using mint = atcoder::modint998244353;

const int MAX = 510000;
mint fac[MAX], finv[MAX], inv[MAX];

void COMinit() {
    const int MOD = mint::mod();
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i;
        inv[i] = MOD - inv[MOD%i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

mint COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[k] * finv[n - k];
}


void solve() {
    COMinit();

    int n; std::cin >> n;
    std::vector<int> a(n);
    for(auto& x : a) std::cin >> x;


    std::array<std::vector<long>, 10> ids;

    int cnt2 = 0, cnt3 = 0;
    int cnt1 = 0, cnt5 = 0, cnt7 = 0;

    mint ans = 1;

    for(int i : std::views::iota(0, n)) {
        if(a[i] % 2 == 0) ++cnt2;
        if(a[i] % 3 == 0) ++cnt3;
        if(a[i] == 6) {
            --cnt2, --cnt3;
            // std::cerr << cnt2 << ", " << cnt3 << "\n";
            ans *= COM(cnt2 + cnt3, cnt3);
            cnt2 = 0;
            cnt3 = 0;
        }
        if(a[i] == 1) ++cnt1;
        if(a[i] == 5) ++cnt5;
        if(a[i] == 7) ++cnt7;
    }

    // std::cerr << cnt2 << ", " << cnt3 << "\n";
    ans *= COM(cnt2+cnt3, cnt3);

    // std::cerr << cnt1 << ", " << cnt5 << ", " << cnt7 << "\n";
    int s = cnt1 + cnt5 + cnt7;

    auto x = (fac[n] * finv[n - s]) * finv[cnt1]* finv[cnt5]* finv[cnt7];
    // std::cerr << x.val() << "\n";
    ans *= x;

    std::cout << ans.val() << "\n";
}
