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

long op(long a, long b) { return a + b; }
long e() { return 0; }
long id() { return 0; }
long comp(long x, long y) { return x + y; }
long map(long f, long x) { return f + x; }

std::vector<std::pair<long long,long long>> convex_hull(std::vector<std::pair<long long,long long>> P){

    if(P.size()<=2){
        return P;
    }
    std::vector<std::pair<long long,long long>> H,L,R;
    sort(P.begin(),P.end());

    for(int i=0;i<P.size();i++){
        int j=L.size();
        while(j>=2 && (L[j-1].first-L[j-2].first)*(P[i].second-L[j-2].second)<=(L[j-1].second-L[j-2].second)*(P[i].first-L[j-2].first)){
            L.pop_back();
            j--;
        }
        L.push_back(P[i]);
    }
    for(int i=P.size()-1;i>=0;i--){
        int j=H.size();
        while(j>=2 && (H[j-1].first-H[j-2].first)*(P[i].second-H[j-2].second)<=(H[j-1].second-H[j-2].second)*(P[i].first-H[j-2].first)){
            H.pop_back();
            j--;
        }
        H.push_back(P[i]);
    }


    R=L;
    for(int i=1;i<H.size()-1;i++){
        R.push_back(H[i]);
    }

    return R;
}

void solve() {
    int n; std::cin >> n;
    std::vector<long> h(n);
    for(auto& v : h) std::cin >> v;

    using P = std::pair<long long, long long>;
    std::vector<P> ps;
    for(int i : std::views::iota(0, n)) {
        ps.emplace_back(i, 0);
        ps.emplace_back(i, h[i]);
    }

    auto convex = convex_hull(ps);
    int m = convex.size();

    long long ans = 0;

    for(int i : std::views::iota(0, m)) {
        auto a = convex[i];
        auto b = convex[(i + 1) % m];

        if(a.second == 0 || b.second == 0) continue;

        ans = std::max(ans, std::abs(a.first - b.first));
    }

    std::cout << ans << "\n";
}
