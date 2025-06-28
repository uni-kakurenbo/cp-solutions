/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
     //std::cin >> $;
    while(true){
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long;

#include "template/warnings.hpp"


void solve() {
    int n, m;
    cin >> n >> m;
    atcoder::dsu ds(n);
    if (n == 0 && m == 0) { exit(0); }
    vector<int> A(m), B(m), S(m), lst(n, 100000);
    vector<vector<int>> ans(n, vector<int>()), sl(100000, vector<int>());
    for (int i=0; i<m; i++) {
        cin >> A[i] >> B[i] >> S[i];
        A[i]--; B[i]--; S[i]--;
        sl[S[i]].push_back(i);
    }
    for (int i=0; i<n; i++) {
        ans[i].push_back(i);
    }
    for (int k : views::iota(0, 100000) | views::reverse){
        for (int i: sl[k]) {
            int u = ds.leader(A[i]), v = ds.leader(B[i]);
            if (ans[u].size() < ans[v].size()) { swap(u, v); }
            if (ds.same(u, v)) { continue; }
            if (ds.size(u) == ds.size(v)) {
                int p = ds.merge(u, v);
                for(auto x : ans[v]) ans[u].push_back(x);
                if (p == v) { swap(ans[u], ans[v]); }
            }
        }
    }
}
